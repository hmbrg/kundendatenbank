//
//  kunde.cpp
//  kundendatenbank
//
//  Created by Matthias Hamborg on 02.02.18.
//  Copyright © 2018 Matthias Hamborg. All rights reserved.
//

#include <string>

#include "kunde.hpp"

/*!
 * \brief Konstruktor Kunde
 *
 * Speichert alle Parameter als Attribute.
 *
 * @param neuFirmenname Name der Firma
 * @param neuVorname Vorname
 * @param neueKundennummer Kundennummer
 * @param neuJahresumsatz Jahresumsatz
 */
Kunde::Kunde(std::string neuFirmenname, std::string neuName, std::string neuVorname, int  neueKundennummer, long neuJahresumsatz) {
    firmenname = neuFirmenname;
    name = neuName;
    vorname = neuVorname;
    kundennummer = neueKundennummer;
    jahresumsatz = neuJahresumsatz;
};

/*!
 * \brief Berechnet den Rabatt eines Kunden
 *
 * Berechnet den Rabatt anhand des Jahresumsatzes.
 *
 * @pre Attribut jahresumsatz muss einen Wert haben.
 * @return int Prozent als Dezimalzahl
 */
const double Kunde::getRabatt() {
    if (jahresumsatz < 10000)
        return 0;
    
    if (jahresumsatz < 20000)
        return 0.01;
    
    if (jahresumsatz < 40000)
        return 0.02;
    
    if (jahresumsatz < 100000)
        return 0.04;
    
    if (jahresumsatz >= 100000)
        return 0.1;
    
    // Wenn Jahresumsatz nicht den geforderten Kriterien enstpricht ist der Rabatt 0%.
    return 0;
};

/*!
 * \brief Setzt den Jahresumsatz
 *
 * Setzt den Jahresumsatz eines existierenden Kundes.
 *
 * @param neuerJahresumsatz Jahresumsatz
 */
void Kunde::setJahresumsatz(long neuerJahresumsatz) {
    jahresumsatz = neuerJahresumsatz;
};
