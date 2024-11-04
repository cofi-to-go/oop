#include "Konto.h"
#include <iostream>
#include <sstream>

int Konto::naechsteKontonummer = 111000;
std::vector<Konto> Konto::alleKonten;

Konto::~Konto()
{
     log("Konto von " + kontoinhaber + " (Konto Nr. " + std::to_string(kontonummer) + ") wird endgültig gelöscht.");
}

void Konto::add_transaction(float betrag)
{
    std::string grund;
    std::cout << "Geben Sie den Grund/Beschreibung für diese Transaktion ein: ";
    std::cin.ignore(); // Clear any leftover input
    std::getline(std::cin, grund);


    Transaktion new_Transaktion(betrag, grund);
    transaktionen.push_back(new_Transaktion);
}

void Konto::transfer(Konto &zielkonto, float betrag, const std::string &grund)
{

    if (betrag > 0 && betrag <= kontostand)
    {
        kontostand -= betrag;
        Transaktion outgoingTransaktion(-betrag,
                                        "Überweisung an Konto" + std::to_string(zielkonto.kontonummer) + ": " + grund);
        transaktionen.push_back(outgoingTransaktion);

        zielkonto.kontostand += betrag;
        Transaktion incomingTransaktion(betrag,
                                        "Überweisung von Konto " + std::to_string(zielkonto.kontonummer) +
                                            " erfolgreich. Grund: " + grund);
        zielkonto.transaktionen.push_back(incomingTransaktion);
        log("Überweisung von " + std::to_string(betrag) + " EUR an " + zielkonto.kontoinhaber +
            " erfolgreich. Grund: " + grund);
        zielkonto.log("Überweisung von " + std::to_string(betrag) + " EUR von " + kontoinhaber +
                      " erhalten. Grund: " + grund);
    }
}


void Konto::bareinzahlung(float betrag)
{
    if (betrag > 0)
    {
        kontostand += betrag;
        add_transaction(betrag);
        std::cout << "Einzahlung von " << betrag << " erfolgreich. Neuer Kontostand: " << kontostand << ".\n";
        log("Bareinzahlung von " + std::to_string(betrag) +
            " EUR erfolgreich. Neuer Kontostand: " + std::to_string(kontostand));
    }
    else
    {
        std::cout << "Ungueltiger Einzahlungsbetrag.\n";
        log("Fehler: Ungültiger Einzahlungsbetrag.");
    }
}

void Konto::barabhebung(float betrag)
{
    if (betrag > 0 && betrag <= kontostand)
    {
        kontostand -= betrag;
        add_transaction(betrag);
        std::cout << "Abhebung von " << betrag << " erfolgreich. Neuer Kontostand: " << kontostand << ".\n";
        log("Bargeldabhebung von " + std::to_string(betrag) +
            " EUR erfolgreich. Neuer Kontostand: " + std::to_string(kontostand));
    }
    else
    {
        std::cout << "Ungueltiger Abhebungsbetrag oder nicht gen�gend Guthaben.\n";
        log("Fehler: Ungültiger Abhebungsbetrag oder nicht genügend Guthaben.");
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
    std::cout << "Neues Konto f�r " << kontoinhaber << " hinzugefuegt.\n";
}

void Konto::zeigeKonten()
{
    for (const auto &konto : alleKonten) // ich verstehe den doppelpunkt nicht
    {
        std::cout << "Kontoinhaber: " << konto.getKontoinhaber() << ", Kontonummer: " << konto.getKontonummer()
                  << ", Kontostand: " << konto.getKontostand() << " EUR\n";
    }
}
void Konto::drucke_kontoauszug() const
{
    if (transaktionen.empty())
    {
        std::cout << "Keine Transaktionen vorhanden. \n";
        return;
    }

    const int transaktionenProSeite = 10;
    double zwischensumme = 0.0;
    int transaktionsNummer = 0;

    for (size_t i = 0; i < transaktionen.size(); ++i)
    {
        const Transaktion &transaktion = transaktionen[i];
        zwischensumme += transaktion.get_betrag();

        std::cout << std::setw(3) << (i + 1) << ". " << transaktion.get_zeitstempel() << " | " << std::setw(10)
                  << transaktion.get_betrag() << " EUR | " << transaktion.get_beschreibung() << "\n";

        transaktionsNummer++;

        if (transaktionsNummer % transaktionenProSeite == 0 || i == transaktionen.size() - 1)
        {
            std::cout << "Zwischensumme: " << std::fixed << std::setprecision(2) << zwischensumme << " EUR\n";
            std::cout << "-----------------------------------------\n";

            if (i != transaktionen.size() - 1)
            {
                std::cout << "Drücken Sie Enter, um die nächste Seite anzuzeigen...";
                std::cin.get(); // Warten, bis der Benutzer Enter drückt
            }
        }
    }
}
void Konto::lade_Konten_csv(const std::string &dateiname)
{
    std::ifstream file(dateiname);

    if (!file.is_open())
    {
        std::cerr << "Fehler beim Öffnen der Datei " << dateiname << " zum Laden.\n";
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
    while (std::getline(file, line))
    {
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
void Konto::exportiere_Konten_csv(const std::string &dateiname = "konten.csv")
{
    // im Anhangsmodus öffnen
    std::ofstream file(dateiname, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Fehler beim Öffnen der Datei " << dateiname << " zum Exportieren.\n";
        return;
    }

    // Überschrift nur hinzufügen, wenn die Datei neu ist oder leer
    std::ifstream checkFile(dateiname);
    if (checkFile.peek() == std::ifstream::traits_type::eof())
    {
        file << "Kontoinhaber,Kontonummer,Kontostand\n";
    }
    checkFile.close();

    // Kontodaten anhängen
    for (const auto &konto : alleKonten)
    {
        file << konto.getKontoinhaber() << "," << konto.getKontonummer() << "," << konto.getKontostand() << "\n";
    }

    file.close();
    std::cout << "Kontodaten wurden erfolgreich in " << dateiname << " exportiert.\n";
}
std::string Konto::getKontoinhaber() const
{
    return kontoinhaber;
}

std::vector<Konto> &Konto::getAlleKonten()
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


//////logging//////

std::ostream *Konto::logger = &std::cout;




void Konto::setLogger(std::ostream &os)
{
    logger = &os;
}


void Konto::log(const std::string &message) const
{
    if (logger)
    {
        // Zeitstempel erstellen
        std::time_t jetzt = std::time(nullptr);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&jetzt));

        // Nachricht zum Logger schreiben
        *logger << "[" << buffer << "] Konto " << kontonummer << " (" << kontoinhaber << "): " << message << "\n";
    }
}
