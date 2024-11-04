#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class Transaktion
{
public:
    //Konstruktor
    Transaktion(double betrag, const std::string &beschreibung);

    //Destruktor
    ~Transaktion();


    double get_betrag() const;
    std::string get_beschreibung() const;


private:
    double m_betrag;
    std::string m_beschreibung;
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

public:
    Konto(const std::string &ki) : kontoinhaber(ki), kontonummer(naechsteKontonummer++) 
    {
        kontostand = 0.0;
        //speichert die aktuelle naechsteKontonummer in der Datei "kontonummer.dat"
        letzteKontonummer();
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


    

    //static void zeige_Transaktionen();
    void add_transaction(double betrag);
    //4e transfer()


};

void date();
