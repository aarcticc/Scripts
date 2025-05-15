#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define RSA_KEY_BITS 2048

int main() {
    int ret;
    RSA *rsa = NULL;
    BIGNUM *bn = NULL;
    FILE *private_key_file = NULL;
    FILE *public_key_file = NULL;

    // Initialisiere die BIGNUM mit Public Exponent 65537
    bn = BN_new();
    ret = BN_set_word(bn, RSA_F4);
    if (ret != 1) {
        fprintf(stderr, "Fehler bei BN_set_word\n");
        return 1;
    }

    // Erzeuge RSA-Key-Pair
    rsa = RSA_new();
    ret = RSA_generate_key_ex(rsa, RSA_KEY_BITS, bn, NULL);
    if (ret != 1) {
        fprintf(stderr, "Fehler bei RSA_generate_key_ex\n");
        return 1;
    }

    // Schreibe privaten Schlüssel in Datei
    private_key_file = fopen("rsa_private.pem", "wb");
    if (!private_key_file) {
        perror("Kann rsa_private.pem nicht öffnen");
        return 1;
    }
    PEM_write_RSAPrivateKey(private_key_file, rsa, NULL, NULL, 0, NULL, NULL);
    fclose(private_key_file);

    // Schreibe öffentlichen Schlüssel in Datei
    public_key_file = fopen("rsa_public.pem", "wb");
    if (!public_key_file) {
        perror("Kann rsa_public.pem nicht öffnen");
        return 1;
    }
    PEM_write_RSA_PUBKEY(public_key_file, rsa);
    fclose(public_key_file);

    // Ressourcen freigeben
    RSA_free(rsa);
    BN_free(bn);

    printf("RSA-Schlüsselpaar wurde erfolgreich erstellt.\n");

    return 0;
}
