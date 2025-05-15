#include <stdio.h>

int main() {
    // Variablendeklaration: Länge, Breite und Fläche in Metern
    double laenge, breite, flaeche;

    // Hinweis für den Benutzer
    printf("Bitte geben Sie die Abmessungen in Metern ein (z. B. 3.5).\n");

    // Eingabe der Länge
    printf("Laenge der Flaeche (m): ");
    if (scanf("%lf", &laenge) != 1 || laenge <= 0) {
        // Fehlerbehandlung bei ungültiger Eingabe
        printf("Ungueltige Eingabe fuer die Laenge. Wert muss > 0 sein.\n");
        return 1;
    }

    // Eingabe der Breite
    printf("Breite der Flaeche (m): ");
    if (scanf("%lf", &breite) != 1 || breite <= 0) {
        // Fehlerbehandlung bei ungültiger Eingabe
        printf("Ungueltige Eingabe fuer die Breite. Wert muss > 0 sein.\n");
        return 1;
    }

    // Berechnung der Fläche
    flaeche = laenge * breite;

    // Ausgabe des Ergebnisses mit zwei Nachkommastellen
    printf("Die Flaeche betraegt: %.2f m^2\n", flaeche);

    return 0; // Programm erfolgreich beendet
}
