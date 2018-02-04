//
//  datenbank.hpp
//  kundendatenbank
//
//  Created by Matthias Hamborg on 02.02.18.
//  Copyright © 2018 Matthias Hamborg. All rights reserved.
//

#pragma once

#include <vector>
#include <string>

#include "kunde.hpp"

/*!
 * \class Datenbank
 *
 * \brief Enthält alle Kunden, verwaltet diese und kann sie Kriterien entsprechend zurückgeben.
 *
 * Datenbank speichert alle Kunden innerhalb eines Vectors. Man kann neue Kunden hinzufügen, sowie existierende löschen.
 * Es ist auch möglich die Kunden nach Jahresumsatz oder Name zu filtern und zurückzugeben.
 * Desweiteren können alle Daten in einer Datei gespeichert werden und aus solcher auch wieder geladen werden.
 *
 */
class Datenbank {
    std::vector<Kunde> kunden;
    
public:    
    bool neuerKunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, long neuJahresumsatz);
    bool neuerKunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, long neuJahresumsatz, int kundenNummer);
    bool entferneKunde(int Kundennummer);
    bool setJahresumsatz(int Kundennummer, long neuerJahresumsatz);
    
    std::vector<Kunde> getKunden();
    std::vector<Kunde> sucheMitName(std::string name);
    std::vector<Kunde> sucheMitUmsatz(long min, long max);
    
    bool laden(std::string dateiName);
    bool speichern(std::string dateiName);
};
