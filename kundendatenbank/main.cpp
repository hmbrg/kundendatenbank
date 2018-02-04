//
//  main.cpp
//  kundendatenbank
//
//  Created by Matthias Hamborg on 31.01.18.
//  Copyright © 2018 Matthias Hamborg. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "kunde.hpp"
#include "datenbank.hpp"

using namespace std;

/*!
 * \brief Gibt Hauptmenü aus und erfragt Auswahl des Benutzers
 *
 * Zeigt das Hauptmenü an und gibt die Auswahl des Nutzers zurück.
 * Hierbei enspricht eine Nummer der Auswahl des Nutzers:
 * 1 = Speichern
 * 2 = Laden
 * 3 = Neuer Kunde
 * 4 = Lösche Kunde
 * 5 = Suche Kunde
 * 6 = Jahresumsatz eines Kunden setzten
 * 7 = Programm beenden
 * 8 = Alle Kunden anzeigen
 *
 * @return int Nummer entspricht der Auswahl des Nutzers
 */
int menu() {
    cout << "\nHauptmenü: [S]peichere Datenbank, [L]ade Datenbank, [N]euer Kunde, Lösch[e] Kunde, S[u]che Kunde, [J]ahresumsatz setzen, [Q] Programm beenden \n";
    cout << "> ";
    string option;
    cin >> option;
    
    if (option == "S") return 1; // Speichern
    if (option == "L") return 2; // Laden
    if (option == "N") return 3; // Neuer Kunde
    if (option == "e") return 4; // Lösche Kunde
    if (option == "u") return 5; // Suche Kunde
    if (option == "J") return 6; // Jahresumsatz setzen
    if (option == "Q") return 7; // Programm beenden
    if (option == "a") return 8; // Alle Kunden ausgeben
    
    return 0;
}

/*!
 * \brief Gibt übergebene Kunden aus
 *
 * Gibt alle übergebenen Kunden in der Konsole aus.
 * Hier bei wird auch überprüft, ob die Menge der Kunden leer ist.
 *
 * @param input Vector von Kunden
 */
void druckeKunden(vector<Kunde> input) {
    if (input.size() < 1) {
        cout << "\nLeider keine Ergebnisse. \n";
        return;
    }
    
    cout << "Gefundene Kunden: " << input.size() << "\n \n";
    
    for (int i = 0; i < input.size(); i++) {
        cout << "Kunde " << input[i].getKundenNummer() << "\n";
        cout << "Firma: " << input[i].getFirmenname() << "\n";
        cout << "Name: " << input[i].getName() << "\n";
        cout << "Vorname: " << input[i].getVorname() << "\n";
        cout << "Jahresumsatz: " << input[i].getJahresumsatz() << "\n";
        cout << "Rabattkategorie: " << (input[i].getRabatt() * 100) << "% \n\n";
    }
}

/*!
 * \brief Führt das Programm aus, wertet die Menueingabe des Nutzers aus und führt diese aus
 *
 * Die main-Funktion hat mehrere Funktionen
 * - Datenbank-Objekt erstellen
 * - Hauptmenu (menu()) anzeigen und die Eingabe auswerten
 * - entsprechend der Eingabe nötige Nutzerabfragen durchführen
 * - die entsprechenen Funktionnen der Datenbank ausführen
 *
 */
int main(int argc, const char * argv[]) {
    
    Datenbank datenbank;
    int option = 0;
    while (option != 7) { // solange wiederholt, bis option = 7, also "Programm beenden"
        option = menu();
        switch (option) {
            case 1: {
                cout << "Dateiname zum Speichern: ";
                string dateiName;
                cin >> dateiName;
                bool res = datenbank.speichern(dateiName);
                
                // bool res gibt an, ob das Ausführen der Funktion erfolgreich war,
                // wenn dies nicht der Fall ist, wird es dem Nutzer angezeigt, sonst Erfolg.
                if (res) {
                    cout << "Speichern war erfolgreich! \n";
                } else {
                    cout << "Fehler beim Speichern! \n";
                }
                break;
            }
            case 2: {
                cout << "Dateiname zum Laden: ";
                string dateiName;
                cin >> dateiName;
                bool res = datenbank.laden(dateiName);
                if (res) { //vgl. oben
                    cout << "Laden war erfolgreich! \n";
                } else {
                    cout << "Fehler beim Laden! \n";
                }
                break;
            }
            case 3: {
                string name, vorname, firma, jahresumsatz;
                
                cout << "Nachname: ";
                cin >> name;
                
                cout << "Vorname: ";
                cin >> vorname;
                
                cout << "Firma: ";
                cin >> firma;
                
                cout << "Jahresumsatz: ";
                cin >> jahresumsatz;
                
                bool res = datenbank.neuerKunde(firma, name, vorname, stol(jahresumsatz));
                if (res) { //vgl. oben
                    cout << "Neuer Eintrag erstellt! \n";
                } else {
                    cout << "Fehler beim Speichern des Eintrags! \n";
                }
                break;
            }
            case 4: {
                cout << "Kundennummer: ";
                string kundennummerString;
                cin >> kundennummerString;
                int kundennummer = stoi(kundennummerString); // Wandelt string in int um
                
                bool res = datenbank.entferneKunde(kundennummer);
                if (res) { //vgl. oben
                    cout << "Eintrag gelöscht! \n";
                } else {
                    cout << "Fehler beim Löschen des Eintrags! \n";
                }
                break;
            }
            case 5: {
                cout << "Suchkriterium: [N]ame, [U]msatz \n> ";
                string kriterium;
                cin >> kriterium;
                
                // Vergleicht weleches Suchkriterium gewählt wurde
                if (kriterium == "N") {
                    cout << "\nName: ";
                    string name;
                    cin >> name;
                    vector<Kunde> results = datenbank.sucheMitName(name);
                    
                    druckeKunden(results);
                    break;
                }
                
                if (kriterium == "U") {
                    cout << "Minimaler Umsatz: ";
                    string minString;
                    cin >> minString;
                    
                    cout << "Maximaler Umsatz: ";
                    string maxString;
                    cin >> maxString;
                    
                    vector<Kunde> results = datenbank.sucheMitUmsatz(stol(minString), stol(maxString)); // stol wandelt string in long um
                    
                    druckeKunden(results);
                    break;
                }
            }
            case 6: {
                string kundennummerString, umsatzString;
                cout << "Kundennummer: \n";
                cin >> kundennummerString;
                cout << "\nJahresumsatz (ohne Einheit): ";
                cin >> umsatzString;
                
                int kundennummer = stoi(kundennummerString); // std::stoi wandelt string in int um
                long umsatz = stol(umsatzString);
                
                bool res = datenbank.setJahresumsatz(kundennummer, umsatz);
                if (res) {
                    cout << "Änderung gespeichert! \n";
                } else {
                    cout << "Fehler beim Ändern des Eintrags! \n";
                }
                break;
            }
            case 7: {
                cout << "Auf Wiedersehen! \n";
                return 0; // main retrun 0 beendet das Programm als erfolgreihc
                break;
            }
            case 8: { // gibt alle kunden der Datenbank aus (nicht im Hauptmenu aufgeführt, siehe Aufgabe)
                druckeKunden(datenbank.getKunden());
                break;
            }
                
            default: // fall-through
                cout << "Keine valide Option, bitte nochmal probieren... \n";
                break;
        }
    }
    return 0;
}
