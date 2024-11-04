#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


class Transaktion
{
public:
    //Konstruktor
    Transaktion(float betrag, const std::string &beschreibung);

    //Destruktor
    ~Transaktion();


    float get_betrag() const;
    std::string get_beschreibung() const;
    std::string get_zeitstempel() const;

private:
    float m_betrag;
    std::string m_beschreibung;
    std::time_t zeitstempel;
};


class Konto
{
private:
    std::string kontoinhaber;
    int kontonummer;
    float kontostand = 0.0;
    std::vector<Transaktion> transaktionen;

    static int naechsteKontonummer;

    static std::vector<Konto> alleKonten;

    //logging
    void log(const std::string &message) const;
    static std::ostream* logger; //statisches logger objekt für alle konten

public:
    Konto(const std::string &ki) : kontoinhaber(ki), kontonummer(naechsteKontonummer++) 
    {
        kontostand = 0.0;
        //speichert die aktuelle naechsteKontonummer in der Datei "kontonummer.dat"
        letzteKontonummer();
        log("Konto erstellt mit Kontoinhaber: " + kontoinhaber + ", Startkontostand: " + std::to_string(kontostand));

    }

    Konto(const Konto& other , const std::string& kopieren) : kontoinhaber(other.kontoinhaber), kontonummer(naechsteKontonummer++), kontostand(0.0) {
        std::cout << "Kopierkonstruktor aufgerufen: " << kontoinhaber << std::endl;
    }
    static void kontoKopieren(const std::string& kontoinhaber);

    //4f Destruktor mit logging
    
    ~Konto() {
        std::cout << "Das Konto wurde geloescht.";
    }

    std::string getKontoinhaber() const;
    static std::vector<Konto> &getAlleKonten();
    int getKontonummer() const;
    float getKontostand() const;


    void setKontoinhaber(std::string ki) { kontoinhaber = ki;}
    void setKontonummer(int kn) { kontonummer = kn; }
    void setKontostand(float ks) { kontostand = ks;}


    void bareinzahlung(float betrag);
    void barabhebung(float betrag);
    //4c close_account(const std::string &kontoinhaber)
    void close_account(const std::string& kontoinhaber, int kontonummer);
    void loesche_konto_csv(const std::string& dateiname, const std::string& kontoinhaber);
    //4d logging()


    static void ladeLetzteKontonummer();
    static void letzteKontonummer();
    static void kontoHinzufuegen(const std::string &kontoinhaber);
    static void zeigeKonten();


    static void exportiere_Konten_csv(const std::string &dateiname);
    static void lade_Konten_csv(const std::string& dateiname);
    void exportiere_transaktionen_csv(const std::string &dateiname);
    void lade_transaktionen_csv(const std::string &dateiname);
    //static void import_Konten_csv();

    void drucke_kontoauszug() const;
    void add_transaction(float betrag);
    void transfer(Konto &zielkonto, float betrag, const std::string &grund);


};

void date();
