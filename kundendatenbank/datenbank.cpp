//
//  datenbank.cpp
//  kundendatenbank
//
//  Created by Matthias Hamborg on 02.02.18.
//  Copyright © 2018 Matthias Hamborg. All rights reserved.
//

#include <vector>
#include <string>
#include <fstream>

#include "datenbank.hpp"
#include "kunde.hpp"

/*!
 * \brief Lädt eine Datenbank aus einer Textdatei
 *
 * Lädt die Datenbank aus Datei, speichert sie als Kunden und sichert sie im kunden-Vector
 *
 * @param dateiName Name der Datenbankdatei
 * @pre Datenbankdatei muss existieren.
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::laden(std::string dateiName) {
    kunden.clear();
    std::ifstream quelle;
    quelle.open(dateiName);
    
    if (quelle.fail()) // Testet ob das Öffnen der Datei erfolgreich war
        return false;

    std::string line, name, vorname, firmenname;
    int kundennummer;
    long jahresumsatz;
    try {
        while (!quelle.eof()) { // Wenn Datei (hier: iostream) zuende ist (EOF = End Of File)
            std::getline(quelle, line);
            
            if (line == "") { // wenn erste Zeile leer ist, ist Datei zuende (zusätzlicher Test)
                return true;
            }
            
            kundennummer = std::stoi(line);
            
            std::getline(quelle, line);
            name = line;
            
            std::getline(quelle, line);
            vorname = line;
            
            std::getline(quelle, line);
            firmenname = line;
            
            std::getline(quelle, line);
            jahresumsatz = std::stol(line);
            
            std::getline(quelle, line); // leere Zeile zwischen Einträgen
            
            Kunde kunde(firmenname, name, vorname, kundennummer, jahresumsatz);
            kunden.push_back(kunde);
        }
    } catch(std::ifstream::failure e) { // Wenn fehler beim Lesen auftreten, wird Fehler zurückgegeben
        return false;
    }
    
    quelle.close();
    return true;
}

/*!
 * \brief Speichert eine Datenbank in einer Textdatei
 *
 * Speichert alle Kunden in einer Textdatei ab.
 *
 * @param dateiName Name der Datenbankdatei
 * @pre Kunden müssen in der Datenbank existieren.
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::speichern(std::string dateiName) {
    if (kunden.size() < 1)
        return false;
    
    std::ofstream sicherung;
    sicherung.open(dateiName);
    
    if (sicherung.fail()) // Testet ob das Öffnen der Datei erfolgreich war
        return false;
    
    for (int i = 0; i < kunden.size(); i++) {
        sicherung << kunden[i].getKundenNummer() << std::endl;
        sicherung << kunden[i].getName() << std::endl;
        sicherung << kunden[i].getVorname() << std::endl;
        sicherung << kunden[i].getFirmenname() << std::endl;
        sicherung << kunden[i].getJahresumsatz() << std::endl;
        sicherung << std::endl;
    }
    
    sicherung.close();
    return true;
}

/*!
 * \brief Erstellt einen neuen Kunden in der Datenbank
 *
 * Erstellt einen neuen Kunden, sucht einen Kundennummer, die noch nicht vergeben ist, und speichert diesen im kunden-Vector.
 *
 * @param neuFirmenname Firmenname
 * @param neuName Nachname
 * @param neuVorname Vorname
 * @param neuJahresumsatz Jahresumsatz
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::neuerKunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, long neuJahresumsatz) {
    int kundennummer = 0;
    // Schleife sucht nach kundennummer, die nicht vergeben ist. Wenn diese schon existiert wird kundennummer + 1
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getKundenNummer() == kundennummer) {
            kundennummer++;
        }
    }
    
    Kunde kunde(neuFirmenname, neuName, neuVorname, kundennummer, neuJahresumsatz);
    kunden.push_back(kunde);
    return true;
}

/*!
 * \brief Erstellt einen neuen Kunden in der Datenbank
 *
 * Erstellt einen neuen Kunden und speichert diesen im kunden-Vector.
 * Hierbei wird allerdings keine Kundennummer generiert, sondern diese schon vorgegeben.
 * Die Kundennummer wird allerdings auf Nichtexistenz überprüft.
 * Diese Funktion ist sinnvoll für das Auslesen aus Datenbankdateien.
 *
 * @param neuFirmenname Firmenname
 * @param neuName Nachname
 * @param neuVorname Vorname
 * @param neuJahresumsatz Jahresumsatz
 * @param kundenummer Kundennummer.
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::neuerKunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, long neuJahresumsatz, int kundenummer) {
    // Überprüft ob Kundennummer schon existiert, wenn ja gibt Fehler
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getKundenNummer() == kundenummer) {
            return false;
        }
    }
    
    Kunde kunde(neuFirmenname, neuName, neuVorname, kundenummer, neuJahresumsatz);
    kunden.push_back(kunde);
    return true;
}

/*!
 * \brief Entfernt Kunden aus der Datenbank
 *
 * Sucht Kunden anhand seiner Kundennummer und entfert diesen aus der Datenbank.
 *
 * @param kundennummer Kundennummer
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::entferneKunde(int kundennummer) {
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getKundenNummer() == kundennummer) {
            kunden.erase(kunden.begin() + i); // Löscht Kunden aus Vector
            return true;
        }
    }
    return false;
}

/*!
 * \brief Ändert den Jahresumsatz eines Kunden
 *
 * Ändert den Jahresumsatz eines Kunden anhand seiner Kundennummer
 *
 * @param Kundennummer Kundennummer
 * @param neuerJahresumsatz neuer Jahresumsatz
 * @return bool true, wenn Ausführung erfolgreich, bei Fehlern false.
 */
bool Datenbank::setJahresumsatz(int Kundennummer, long neuerJahresumsatz) {
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getKundenNummer() == Kundennummer) {
            kunden[i].setJahresumsatz(neuerJahresumsatz);
            return true;
        }
    }
    return false;
}

/*!
 * \brief Gibt alle Kunden der Datenbank zurück
 *
 * Gibt den gesamten kunden-Vector zurück.
 *
 * @return vector<Kunde> Vector mit allen Kunden der Datenbank
 */
std::vector<Kunde> Datenbank::getKunden() {
    return kunden;
}

/*!
 * \brief Sucht nach Kunden mit gegebenem Namen
 *
 * Gibt alle Kunden mit einem bestimmtem Namen zurück.
 *
 * @param name Name
 * @return vector<Kunde> Vector mit Kunden
 */
std::vector<Kunde> Datenbank::sucheMitName(std::string name) {
    std::vector<Kunde> ergebnisse;
    
    // Vergleicht alle Kunden mit Kriterium, wenn wahr, dann wird Kunde in ergebnisse-Vector hinzugefügt
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getName() == name) {
            ergebnisse.push_back(kunden[i]);
        }
    }
    return ergebnisse;
}

/*!
 * \brief Sucht nach Kunden mit gegebenem Jahresumsatz
 *
 * Gibt alle Kunden mit einem bestimmtem Jahresumsatz, welcher zwischen zwei Werten liegt, zurück.
 *
 * @param min minimaler Jahresumsatz
 * @param max maximaler Jahresumsatz
 * @return vector<Kunde> Vector mit Kunden
 */
std::vector<Kunde> Datenbank::sucheMitUmsatz(long min, long max) {
    std::vector<Kunde> ergebnisse;
    
    // Vergleicht alle Kunden mit Kriterium, wenn wahr, dann wird Kunde in ergebnisse-Vector hinzugefügt
    for (int i = 0; i < kunden.size(); i++) {
        if (kunden[i].getJahresumsatz() >= min && kunden[i].getJahresumsatz() <= max) {
            ergebnisse.push_back(kunden[i]);
        }
    }
    return ergebnisse;
}
