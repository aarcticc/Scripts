#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>

#define OUTPUT_DIR "keygen-output"

// Funktion zum Schreiben von Base64-kodierten Schlüsseln mit Header/Footern
void write_base64_file(const char *filename, const char *header, BYTE *data, DWORD len) {
    DWORD base64Len = 0;
    char *base64 = NULL;

    // Berechnung der notwendigen Größe für Base64-Daten
    if (!CryptBinaryToStringA(data, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &base64Len)) {
        printf("Fehler bei Größenberechnung für Base64.\n");
        return;
    }

    base64 = (char *)malloc(base64Len);
    if (!CryptBinaryToStringA(data, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, base64, &base64Len)) {
        printf("Fehler beim Base64-Encoding.\n");
        free(base64);
        return;
    }

    // Datei öffnen und Header + Base64 schreiben
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Fehler beim Öffnen der Datei: %s\n", filename);
        free(base64);
        return;
    }

    fprintf(fp, "-----BEGIN %s-----\n", header);
    for (DWORD i = 0; i < base64Len; i++) {
        fputc(base64[i], fp);
        if ((i + 1) % 64 == 0) fputc('\n', fp);  // Zeilenumbruch alle 64 Zeichen
    }
    fputc('\n', fp);
    fprintf(fp, "-----END %s-----\n", header);
    fclose(fp);
    free(base64);
}

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hKey = 0;
    BYTE *privateBlob = NULL;
    BYTE *publicBlob = NULL;
    DWORD privLen = 0, pubLen = 0;

    // Erstellen des Ausgabeordners (falls nicht vorhanden)
    if (!CreateDirectoryA(OUTPUT_DIR, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        printf("Konnte das Verzeichnis nicht erstellen.\n");
        return 1;
    }

    // Kryptografischen Kontext erzeugen
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext fehlgeschlagen.\n");
        return 1;
    }

    // RSA-Schlüsselpaar generieren (2048 Bit, exportierbar)
    if (!CryptGenKey(hProv, AT_KEYEXCHANGE, 2048 << 16 | CRYPT_EXPORTABLE, &hKey)) {
        printf("CryptGenKey fehlgeschlagen.\n");
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Exportieren des öffentlichen Schlüssels
    if (!CryptExportKey(hKey, 0, PUBLICKEYBLOB, 0, NULL, &pubLen)) {
        printf("Fehler beim Ermitteln der Größe des öffentlichen Schlüssels.\n");
        goto cleanup;
    }
    publicBlob = (BYTE *)malloc(pubLen);
    if (!CryptExportKey(hKey, 0, PUBLICKEYBLOB, 0, publicBlob, &pubLen)) {
        printf("Export des öffentlichen Schlüssels fehlgeschlagen.\n");
        goto cleanup;
    }

    // Exportieren des privaten Schlüssels
    if (!CryptExportKey(hKey, 0, PRIVATEKEYBLOB, 0, NULL, &privLen)) {
        printf("Fehler beim Ermitteln der Größe des privaten Schlüssels.\n");
        goto cleanup;
    }
    privateBlob = (BYTE *)malloc(privLen);
    if (!CryptExportKey(hKey, 0, PRIVATEKEYBLOB, 0, privateBlob, &privLen)) {
        printf("Export des privaten Schlüssels fehlgeschlagen.\n");
        goto cleanup;
    }

    // Speichern beider Schlüssel als Base64-codierte .PEM-Dateien
    write_base64_file(OUTPUT_DIR "\\rsa_public.pem", "RSA PUBLIC KEY", publicBlob, pubLen);
    write_base64_file(OUTPUT_DIR "\\rsa_private.pem", "RSA PRIVATE KEY", privateBlob, privLen);
    printf("RSA-Schlüsselpaar erfolgreich generiert in '%s'\n", OUTPUT_DIR);

cleanup:
    if (publicBlob) free(publicBlob);
    if (privateBlob) free(privateBlob);
    if (hKey) CryptDestroyKey(hKey);
    if (hProv) CryptReleaseContext(hProv, 0);

    return 0;
}
