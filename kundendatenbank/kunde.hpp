//
//  kunde.hpp
//  kundendatenbank
//
//  Created by Matthias Hamborg on 31.01.18.
//  Copyright © 2018 Matthias Hamborg. All rights reserved.
//

#pragma once

#include <string>

/*!
 * \class Kunde
 *
 * \brief Enthält Informationen über einen Kunden.
 *
 * Kunde speichert Informationen wie den Namen, die Kundennummer und die Firma eines Kunden.
 * Auch berechnet sie die Rabattkategorie und kann den Jahresumsatz ändern.
 *
 */
class Kunde {
    std::string firmenname;
    std::string name;
    std::string vorname;
    int kundennummer;
    long jahresumsatz;
    
public:
    Kunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, int  neueKundennummer, long neuJahresumsatz);
    
    const std::string getFirmenname() { return firmenname; };
    const std::string getName() { return name; };
    const std::string getVorname() { return vorname; };
    const int getKundenNummer() { return kundennummer; };
    const long getJahresumsatz() { return jahresumsatz; };
    
    const double getRabatt();
    
    void setJahresumsatz(long neuerJahresumsatz);
};

