import customtkinter as ctk
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.backends import default_backend
import zipfile
import os
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email import encoders
import re

class RSAKeyGenApp:
    def __init__(self):
        self.app = ctk.CTk()
        self.app.title("RSA Key Generator")
        self.app.geometry("400x500")
        self.app.configure(fg_color="#1E1E1E")
        
        # Configure theme
        ctk.set_appearance_mode("dark")
        ctk.set_default_color_theme("blue")
        
        # Create main frame
        self.main_frame = ctk.CTkFrame(self.app, fg_color="#2D2D2D")
        self.main_frame.pack(padx=20, pady=20, fill="both", expand=True)
        
        # Title
        self.title_label = ctk.CTkLabel(
            self.main_frame,
            text="RSA Key Generator",
            font=("SF Pro Display", 24, "bold")
        )
        self.title_label.pack(pady=20)
        
        # Email input
        self.email_label = ctk.CTkLabel(
            self.main_frame,
            text="Email Address:",
            font=("SF Pro Display", 14)
        )
        self.email_label.pack(pady=(20, 5))
        
        self.email_entry = ctk.CTkEntry(
            self.main_frame,
            width=300,
            placeholder_text="Enter your email"
        )
        self.email_entry.pack(pady=(0, 20))
        
        # Key size selection
        self.key_size_label = ctk.CTkLabel(
            self.main_frame,
            text="Key Size:",
            font=("SF Pro Display", 14)
        )
        self.key_size_label.pack(pady=(20, 5))
        
        self.key_size_var = ctk.StringVar(value="2048")
        self.key_size_menu = ctk.CTkOptionMenu(
            self.main_frame,
            values=["2048", "3072", "4096"],
            variable=self.key_size_var
        )
        self.key_size_menu.pack(pady=(0, 20))
        
        # Generate button
        self.generate_button = ctk.CTkButton(
            self.main_frame,
            text="Generate and Send Keys",
            command=self.generate_and_send_keys,
            font=("SF Pro Display", 14)
        )
        self.generate_button.pack(pady=20)
        
        # Status label
        self.status_label = ctk.CTkLabel(
            self.main_frame,
            text="",
            font=("SF Pro Display", 12)
        )
        self.status_label.pack(pady=20)

    def validate_email(self, email):
        pattern = r'^[\w\.-]+@[\w\.-]+\.\w+$'
        return re.match(pattern, email) is not None

    def generate_key_pair(self):
        key_size = int(self.key_size_var.get())
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=key_size,
            backend=default_backend()
        )
        public_key = private_key.public_key()
        return private_key, public_key

    def save_keys_to_zip(self, private_key, public_key, email):
        # Create temporary files
        private_pem = private_key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption()
        )
        
        public_pem = public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )
        
        zip_filename = f"rsa_keys_{email}.zip"
        with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zip_file:
            zip_file.writestr('private_key.pem', private_pem)
            zip_file.writestr('public_key.pem', public_pem)
            
        return zip_filename

    def send_email_with_keys(self, zip_filename, recipient_email):
        # Note: Replace with your email credentials
        sender_email = "your_email@gmail.com"
        sender_password = "your_app_password"
        
        msg = MIMEMultipart()
        msg['From'] = sender_email
        msg['To'] = recipient_email
        msg['Subject'] = "Your RSA Keys"
        
        body = "Please find your RSA key pair attached. Keep the private key secure and never share it."
        msg.attach(MIMEText(body, 'plain'))
        
        with open(zip_filename, 'rb') as attachment:
            part = MIMEBase('application', 'zip')
            part.set_payload(attachment.read())
            encoders.encode_base64(part)
            part.add_header(
                'Content-Disposition',
                f'attachment; filename= {zip_filename}'
            )
            msg.attach(part)
        
        try:
            server = smtplib.SMTP('smtp.gmail.com', 587)
            server.starttls()
            server.login(sender_email, sender_password)
            server.send_message(msg)
            server.quit()
            return True
        except Exception as e:
            print(f"Error sending email: {e}")
            return False

    def generate_and_send_keys(self):
        email = self.email_entry.get().strip()
        
        if not self.validate_email(email):
            self.status_label.configure(text="Invalid email address!", text_color="red")
            return
        
        self.status_label.configure(text="Generating keys...", text_color="white")
        self.app.update()
        
        try:
            private_key, public_key = self.generate_key_pair()
            zip_filename = self.save_keys_to_zip(private_key, public_key, email)
            
            self.status_label.configure(text="Sending email...", text_color="white")
            self.app.update()
            
            if self.send_email_with_keys(zip_filename, email):
                self.status_label.configure(
                    text="Keys generated and sent successfully!",
                    text_color="green"
                )
            else:
                self.status_label.configure(
                    text="Error sending email. Keys generated but not sent.",
                    text_color="red"
                )
            
            # Cleanup
            if os.path.exists(zip_filename):
                os.remove(zip_filename)
                
        except Exception as e:
            self.status_label.configure(
                text=f"Error: {str(e)}",
                text_color="red"
            )

    def run(self):
        self.app.mainloop()

if __name__ == "__main__":
    app = RSAKeyGenApp()
    app.run()
