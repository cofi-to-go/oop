#include "Konto.h"


//Konstruktor
Transaktion::Transaktion( double betrag, const std::string &beschreibung)
    : m_betrag(betrag), m_beschreibung(beschreibung)
{
    //date is today, when you add date to the class
}

Transaktion::~Transaktion()
{
}

double Transaktion::get_betrag() const
{
    return m_betrag;
}
std::string Transaktion::get_beschreibung() const
{
    return m_beschreibung;
}

void date()
{
    time_t ti = time(NULL);
    tm *datePtr = localtime(&ti);

    std::cout << "Datum: " << (datePtr->tm_mday) << "/" << (datePtr->tm_mon) + 1 << "/" << (datePtr->tm_year) + 1900
              << ":";
}
