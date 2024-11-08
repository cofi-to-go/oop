#include "Konto.h"
#include <iostream>

Konto *findeKonto(const std::string &kontoinhaber)
{
    for (auto &konto : Konto::getAlleKonten())
    {
        if (konto.getKontoinhaber() == kontoinhaber)
        {
            return &konto; // Rueckgabe von gefundenem Konto
        }
    }
    return nullptr;
}
int findeKontonr(int kontonummer)
{
    for (auto& konto : Konto::getAlleKonten())
    {
        if (konto.getKontonummer() == kontonummer)
        {
            return 1;
        }
    }
    return 0;
}
Konto* findeKonto(const int kontonummer)
{
    for (auto& konto : Konto::getAlleKonten())
    {
        if (konto.getKontonummer() == kontonummer)
        {
            return &konto; // Rueckgabe von gefundenem Konto
        }
    }
    return nullptr;
}

int main()
{
    std::string logOption;
    std::ofstream logfile;

    // Benutzerabfrage, ob Log in Datei oder in Konsole erfolgen soll
    std::cout << "Wo möchten Sie das Log speichern? (1: Konsole, 2: Datei): ";
    std::getline(std::cin, logOption);

    if (logOption == "2")
    {
        logfile.open("konto_log.txt");
        if (logfile.is_open())
        {
            Konto::setLogger(logfile);
            std::cout << "Logging wird in Datei 'konto_log.txt' geschrieben.\n";
        }
        else
        {
            std::cerr << "Fehler: Log-Datei konnte nicht geöffnet werden, es wird auf die Konsole geloggt.\n";
        }
    }
    else
    {
        // Standardmäßig wird auf die Konsole geloggt
        Konto::setLogger(std::cout);
        std::cout << "Logging erfolgt auf die Konsole.\n";
    }


    Konto::ladeLetzteKontonummer(); // Laedt die letzte Kontonummer
    std::string name;
    Konto::lade_Konten_csv("test.csv");

    while (true)
    {
        std::cout << "Geben Sie den Namen des Kontoinhabers an (exit um Eingabe zu beenden): ";
        std::getline(std::cin, name);

        if (name == "exit")
        {
            break;
        }
        Konto::kontoHinzufuegen(name);
    }

    int auswahl;
    while (true)
    {
        std::cout << "Was moechten Sie nun tun?\n"
                  << "1: Bareinzahlung\n"
                  << "2: Barabhebung\n"
                  << "3: Konten anzeigen\n"
                  << "4: Kontoauszug drucken\n"
                  << "5: Kontodaten in Textdatei speichern\n"
                  << "6: Konto kopieren\n"
                  << "7: Überweisung\n"
                  << "8: Konto schliessen\n"
                  << "9: Programm beenden\n";

        std::cout << "Bitte wählen Sie eine Option: ";
        std::cin >> auswahl;
        std::cin.ignore(); // Eingabepuffer leeren

        switch (auswahl)
        {
        case 1:
        {
            std::string kontoinhaber;
            int kontonummer;
            float betrag;

            std::cout << "Geben Sie den Namen des Kontoinhabers ein: ";
            std::getline(std::cin, kontoinhaber);
            std::cout << "Geben Sie die Kontonummer ein: ";
            std::cin >> kontonummer;
            Konto* konto = findeKonto(kontonummer);

            if (konto)
            {
                std::cout << "Geben Sie den Betrag ein, den Sie einzahlen moechten: ";
                std::cin >> betrag;
                konto->bareinzahlung(betrag);
            }
            else
            {
                std::cout << "Konto nicht gefunden.\n";
            }
            break;
        }
        case 2:
        {
            std::string kontoinhaber;
            int kontonummer;
            float betrag;

            std::cout << "Geben Sie den Namen des Kontoinhabers ein: ";
            std::getline(std::cin, kontoinhaber);
            std::cout << "Geben Sie die Kontonummer ein: ";
            std::cin >> kontonummer;
            Konto *konto = findeKonto(kontonummer);

            if (konto)
            {
                std::cout << "Geben Sie den Betrag ein, den Sie abheben moechten: ";
                std::cin >> betrag;
                konto->barabhebung(betrag);
            }
            else
            {
                std::cout << "Konto nicht gefunden.\n";
            }
            break;
        }
        case 3:
            Konto::zeigeKonten();
            break;
        case 4:
        {
            std::string kontoinhaber;
            std::cout << "Geben Sie den Namen des Kontoinhabers ein: ";
            std::getline(std::cin, kontoinhaber);

            Konto *konto = findeKonto(kontoinhaber);

            if (konto)
            {
                std::cout << "Konto gefunden.\n";
                konto->drucke_kontoauszug();
            }
            else
            {
                std::cout << "Konto nicht gefunden.\n";
            }
            break;
        }
            std::cout << "formatierter Kontoauszug:\n";
            break;
        case 5:
            std::cout << "Kontdaten erfolgreich in Textdatei gespeichert.\n";
            Konto::exportiere_Konten_csv("test.csv");
            break;
        case 6:
        {
            std::string name;
            std::cout << "Konto von Kontoinhaber kopieren: ";
            std::getline(std::cin, name);
            Konto::kontoKopieren(name);
            break;

        }
        case 7:
        {
            std::string kontoinhaber;
            std::string zielkontoinhaber;
            float betrag;
            std::string grund;
            int kontonummer;

            std::cout << "Geben Sie den Namen des Kontoinhabers ein: ";
            std::getline(std::cin, kontoinhaber);
            Konto *konto = findeKonto(kontoinhaber);

            if (!konto)
            {
                std::cout << "Konto nicht gefunden.\n";
                break;
            }

            std::cout << "Geben Sie den Namen des Zielkontos ein: ";
            std::getline(std::cin, zielkontoinhaber);
            Konto *zielkonto = findeKonto(zielkontoinhaber);

            if (!zielkonto)
            {
                std::cout << "Konto nicht gefunden.\n";
                break;
            }

            // Benutzer nach dem Überweisungsbetrag fragen
            std::cout << "Geben Sie den Betrag ein, den Sie überweisen möchten: ";
            std::cin >> betrag;
            std::cin.ignore(); // Eingabepuffer bereinigen

            std::cout << "Geben sie den Grund für die Überweisung ein: ";
            std::getline(std::cin, grund);

            if (konto != zielkonto)
            {
                konto->transfer(*zielkonto, betrag, grund);
            }
            else
            {
                std::cout << "Fehler: Das Zielkonto darf nicht das gleiche sein wie das Senderkonto.\n";
            }
            break;
        }


        case 8:
            {
            std::string kontoinhaber;
            int kontonummer;

            std::cout << "Geben Sie den Namen des Kontoinhabers ein: ";
            std::getline(std::cin, kontoinhaber);
            std::cout << "Geben Sie die Kontonummer ein: ";
            std::cin >> kontonummer;
            if (findeKontonr(kontonummer) == 1) {
                Konto* konto = findeKonto(kontoinhaber);

                if (konto)
                {
                    konto->close_account(kontoinhaber, kontonummer);
                }
                else {
                    std::cout << "Konto nicht gefunden";
                }
            }
            else { std::cout << "Diese Kontonummer existiert nicht."; }
            break;
        }
        case 9:
            return 0;
        default:
            std::cout << "Ungueltige Auswahl.\n";
            break;

        }


    return 0;
}
