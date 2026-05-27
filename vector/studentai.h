#ifndef STUDENTAI_H
#define STUDENTAI_H

#pragma once
#include <iostream>
//#include <Vector>
#include <string>
#include <algorithm>
#include "Vector2.h"

//using namespace std;

namespace my {
    template <typename T>
    using Vector = ::Vector<T>;
}

const Vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const Vector<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
const Vector<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
const Vector<string> mgalunes = {"as", "aitis"};
const Vector<string> fgalunes = {"iene", "aite", "yte"};

enum class SkirstymoStrategija //! Strategijos studentų skirstymui
{
    PIRMAS,
    ANTRAS,
    TRECIAS
};
 //! Bazinė abstrakti klasė Zmogus
class Zmogus {
protected:
    string vardas;
    string pavarde;

public:
    //! Bazinis konstruktorius
    Zmogus(const string& v = "A", const string& p = "BB")
    : vardas(v), pavarde(p)
    {}
    //! Virtualus destruktorius
    virtual ~Zmogus() {}

    //! Abstrakti informacijos funkcija
    virtual void info() const = 0; // kad veiktu abstrakciai

    string& refVardas() { return vardas; }
    string& refPavarde() { return pavarde; }
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }

    //! Rule of Zero (default) copy/move
    Zmogus(const Zmogus&) = default;
    Zmogus& operator=(const Zmogus&) = default;
    Zmogus(Zmogus&&) noexcept = default;
    Zmogus& operator=(Zmogus&&) noexcept = default;
};

//! Studentas klasė, paveldi iš Zmogus
class Studentas : public Zmogus {
private:
    Vector<int> paz;
    int egz = 0;
    double rez = 0.0;
    double medrez = 0.0;

public:
    //! Konstruktorius su pažymiais ir egzaminu
    Studentas(const string& v = "A",
          const string& p = "BB",
          const Vector<int>& paz_ = {},
          int egz_ = 0)
    : Zmogus(v, p),          // zmogaus konstruktorius
      paz(paz_),
      egz(egz_),
      rez(0.0),
      medrez(0.0)
{
    vardas = v;
    pavarde = p;

    if (!paz.empty())
        skaiciuoti();
}

~Studentas()
{
    paz.clear();
}

// Rule of Five

Studentas(const Studentas& other) //! Kopijavimo konstruktorius
    : Zmogus(other),
      paz(other.paz),
      egz(other.egz),
      rez(other.rez),
      medrez(other.medrez)
{}

//! Kopijavimo operatorius
Studentas& operator=(const Studentas& other) { 
    if (this != &other) {
        Zmogus::operator=(other);
        paz = other.paz;
        egz = other.egz;
        rez = other.rez;
        medrez = other.medrez;
    }
    return *this;
}

//! move konstruktorius
Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other)),
      paz(std::move(other.paz)),
      egz(other.egz),
      rez(other.rez),
      medrez(other.medrez)
{
    other.egz = 0;
    other.rez = 0;
    other.medrez = 0;
}

//! move operatorius
Studentas& operator=(Studentas&& other) noexcept {
    if (this != &other) {
        Zmogus::operator=(std::move(other));
        paz = std::move(other.paz);
        egz = other.egz;
        rez = other.rez;
        medrez = other.medrez;

        other.egz = 0;
        other.rez = 0;
        other.medrez = 0;
    }
    return *this;
}

    void info() const override { // kad veiktu ne abstrakciai?
        cout << "Studentas: " << vardas << " " << pavarde << endl;
    }

    Vector<int>& refPaz() { return paz; }
    int& refEgz() { return egz; }
    double& refRez() { return rez; }
    double& refMedrez() { return medrez; }
    void clearPaz() { paz.clear(); }
    double getRez() const { return rez; }
    double getMedrez() const { return medrez; }
    int getEgz() const { return egz; }

    const Vector<int>& getPaz() const { return paz; }

    void addPaz(int p) { paz.push_back(p); }
    void setEgz(int e) { egz = e; }


    void skaiciuoti(); //! rezultatu skaiciavimas
};

const string irasymo_failas = "kursiokai.txt";
const string irasymo_failas_geras = "kursiokai_geri.txt";
const string irasymo_failas_blogas = "kursiokai_blogi.txt";

void inputas(Vector<Studentas> &grupe);
void failinputas(Vector<Studentas> &grupe, string reading);
void randominputas(Vector<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const Vector<Studentas> &grupe);
void failoutputas(const Vector<Studentas> &grupe, string writing);
void failgeneravimas();
void genirasymas(Vector<Studentas> &grupe, Vector<Studentas> &protingi, Vector<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);
void rikiuoti(Vector<Studentas> &grupe, int pasirinkimas);
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);
void skirstyti(const Vector<Studentas>& grupe, Vector<Studentas>& protingi, Vector<Studentas>& neprotingi);
void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t);
void skirstyti2(Vector<Studentas>& grupe, Vector<Studentas>& neprotingi);
void skirstyti3(Vector<Studentas>& grupe, Vector<Studentas>& neprotingi);

ostream& operator<<(ostream& os, const Studentas& s);
istream& operator>>(istream& is, Studentas& s);


#endif