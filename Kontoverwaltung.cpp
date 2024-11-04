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
        std::cout << "Was moechten Sie nun tun? \n1: Bareinzahlung\n2: Barabhebung\n3: Konten anzeigen\n4: Kontoauszug "
                     "drucken\n5: Kontodaten in Textdatei speichern\n 6: neues Konto mit selben Kontoinhaber anlegen\n 7: Konto schliessen\n 8: Programm beenden\n";
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
                //konto->zeige_Transaktionen(); // Correct: calling printTransactions on a specific Konto instance
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
        case 8:
            return 0; //Programm beenden
        default:
            std::cout << "Ungueltige Auswahl.\n";
            break;
        }
    }

    return 0;
}
