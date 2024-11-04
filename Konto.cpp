#include "Konto.h"
#include <iostream>
#include <sstream>

int Konto::naechsteKontonummer = 111000;
std::vector<Konto> Konto::alleKonten;
std::string Konto::getKontoinhaber() const
{
    return kontoinhaber;
}

std::vector<Konto>& Konto::getAlleKonten()
{
    return alleKonten;
}

int Konto::getKontonummer() const
{
    return kontonummer;
}

float Konto::getKontostand() const
{
    return kontostand;
}

void Konto::add_transaction(double betrag)
{
    std::string grund;
    std::cout << "Geben Sie den Grund/Beschreibung für diese Transaktion ein: ";
    std::cin.ignore();  // Clear any leftover input
    std::getline(std::cin, grund);


    Transaktion new_Transaktion(betrag, grund);
    transaktionen.push_back(new_Transaktion);

}

void Konto::kontoKopieren(const std::string& kontoinhaber) {
    for (const auto& konto : Konto::getAlleKonten()) {
        if (konto.getKontoinhaber() == kontoinhaber) {
            Konto neuesKonto(konto, "kopieren"); // Kopierkonstruktor aufrufen
            alleKonten.push_back(neuesKonto); 
            std::cout << "Neues Konto fuer " << kontoinhaber << " wurde kopiert." << std::endl;
            return; 
        }
    }
    std::cout << "Konto fuer " << kontoinhaber << " nicht gefunden." << std::endl;
}

void Konto::bareinzahlung(float betrag)
{
    if (betrag > 0)
    {
        kontostand += betrag;
        add_transaction(betrag);
        std::cout << "Einzahlung von " << betrag << " erfolgreich. Neuer Kontostand: " << kontostand << ".\n";

    }
    else
    {
        std::cout << "Ungueltiger Einzahlungsbetrag.\n";
    }
}

void Konto::barabhebung(float betrag)
{
    if (betrag > 0 && betrag <= kontostand)
    {
        kontostand -= betrag;
        add_transaction(betrag);
        std::cout << "Abhebung von " << betrag << " erfolgreich. Neuer Kontostand: " << kontostand << ".\n";
        //add_transaction(betrag);
    }
    else
    {
        std::cout << "Ungueltiger Abhebungsbetrag oder nicht gen�gend Guthaben.\n";
    }
}

void Konto::ladeLetzteKontonummer()
{
    std::ifstream datei("kontonummer.dat");
    if (datei.is_open())
    {
        datei >> naechsteKontonummer;
        datei.close();
    }
    else
    {
        naechsteKontonummer = 111000; // Startwert, wenn Datei nicht existiert
    }
}

void Konto::letzteKontonummer()
{
    std::ofstream datei("kontonummer.dat");
    if (datei.is_open())
    {
        datei << naechsteKontonummer;
        datei.close();
    }
}

void Konto::kontoHinzufuegen(const std::string &kontoinhaber)
{
    Konto neuesKonto(kontoinhaber);
    alleKonten.push_back(neuesKonto);
    std::cout << "Neues Konto fuer " << kontoinhaber << " hinzugefuegt.\n";
}

void Konto::zeigeKonten()
{
    for (const auto &konto : alleKonten)// ich verstehe den doppelpunkt nicht
    {
        std::cout << "Kontoinhaber: " << konto.getKontoinhaber() << ", Kontonummer: " << konto.getKontonummer()
                  << ", Kontostand: " << konto.getKontostand() << " EUR\n";
    }
}
/*
 void Konto::zeige_Transaktionen()
 {
     if (transaktionen.empty()) {
        std::cout << "Keine Transaktionen vorhanden.\n";
    } else {
        std::cout << "Transaktionsübersicht:\n";
        for (const auto& transaktion : transaktionen) {
            std::cout << "Betrag: " << transaktion.get_betrag()
                      << ", Beschreibung: " << transaktion.get_beschreibung() << "\n";
        }
    }
 }
 */
void Konto::lade_Konten_csv(const std::string& dateiname)
{
    std::ifstream file(dateiname);

    if (!file.is_open()) {
        std::cerr << "Fehler beim Oeffnen der Datei " << dateiname << " zum Laden.\n";
        return;
    }

    // Den Header überspringen
    std::string header;
    std::getline(file, header);

    // Variablen zum Einlesen der Daten
    std::string line;
    std::string kontoinhaber;
    int kontonummer;
    float kontostand;

    // Datei zeilenweise einlesen
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        
        std::getline(ss, kontoinhaber, ',');

        
        std::getline(ss, token, ',');
        kontonummer = std::stoi(token);

        
        std::getline(ss, token, ',');
        kontostand = std::stof(token);

        // Neues Konto erstellen und Werte zuweisen
        Konto neuesKonto(kontoinhaber);
        neuesKonto.setKontonummer(kontonummer); 
        neuesKonto.setKontostand(kontostand);   
        alleKonten.push_back(neuesKonto);       
    }

    file.close();
    std::cout << "Kontodaten wurden erfolgreich aus " << dateiname << " geladen.\n";
}
void Konto::exportiere_Konten_csv(const std::string& dateiname = "konten.csv")
{
    std::ofstream file(dateiname);
    file << "Kontoinhaber,Kontonummer,Kontostand\n";

    for (const auto& konto : alleKonten)
    {
        file << konto.getKontoinhaber() << "," << konto.getKontonummer() << "," << konto.getKontostand() << "\n";
    }

    file.close();
    std::cout << "Kontodaten wurden erfolgreich in " << dateiname << " exportiert.\n";
}
/*
void Konto::exportiere_Konten_csv(const std::string& dateiname = "konten.csv")
{
    // im Anhangsmodus öffnen
    std::ofstream file(dateiname, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Fehler beim Oeffnen der Datei " << dateiname << " zum Exportieren.\n";
        return;
    }

    // Überschrift nur hinzufügen, wenn die Datei neu ist oder leer
    std::ifstream checkFile(dateiname);
    if (checkFile.peek() == std::ifstream::traits_type::eof()) {
        file << "Kontoinhaber,Kontonummer,Kontostand\n";
    }
    checkFile.close();

    // Kontodaten anhängen
    for (const auto& konto : alleKonten) {
        file << konto.getKontoinhaber() << "," << konto.getKontonummer() << "," << konto.getKontostand() << "\n";
    }

    file.close();
    std::cout << "Kontodaten wurden erfolgreich in " << dateiname << " exportiert.\n";
}*/

void Konto::loesche_konto_csv(const std::string& dateiname, const std::string& kontoinhaber) {
    std::ifstream inputFile(dateiname);
    std::vector<std::string> lines; 

    if (!inputFile.is_open()) {
        std::cerr << "Fehler beim Oeffnen der Datei!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    // Suchen und Löschen der Zeile mit dem angegebenen Kontoinhaber
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        std::istringstream iss(*it);
        std::string name;
        std::getline(iss, name, ',');

        if (name == kontoinhaber) {
            lines.erase(it);
            std::cout << "Konto von " << kontoinhaber << " wurde in Datei geloescht." << std::endl;
            break; 
        }
    }

    std::ofstream outputFile(dateiname);
    for (const auto& line : lines) {
        outputFile << line << std::endl; // restlichen Zeilen zurück in die Datei
    }
    outputFile.close();


}

void Konto::close_account(const std::string& kontoinhaber, int kontonummer) {
    for (auto it = Konto::getAlleKonten().begin(); it != Konto::getAlleKonten().end(); ++it) {
        if (it->getKontoinhaber() == kontoinhaber && it->getKontonummer() == kontonummer) {
            if (it->getKontostand() != 0.0f) {
                std::cout << "Der Kontostand ist nicht 0. Bitte ueberweisen Sie das restliche Guthaben." << std::endl;
                return;
            }

            // Löschen (Destruktor wird automatisch aufgerufen)
            std::cout << "Das Konto von " << kontoinhaber << " wird geschlossen." << std::endl;
            alleKonten.erase(it); 
            Konto::loesche_konto_csv("test.csv", kontoinhaber);

            return;
        }
    }

    std::cout << "Konto fuer " << kontoinhaber << " nicht gefunden." << std::endl;
}

