#ifndef STUDENTAI_H
#define STUDENTAI_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const vector<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
const vector<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
const vector<string> mgalunes = {"as", "aitis"};
const vector<string> fgalunes = {"iene", "aite", "yte"};

enum class SkirstymoStrategija
{
    PIRMAS,
    ANTRAS,
    TRECIAS
};

class Zmogus {
protected:
    string vardas;
    string pavarde;

public:
    virtual ~Zmogus() = default;

    // Pure virtual function makes class abstract
    virtual void info() const = 0;

    // Common getters/setters
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }
};


class Studentas : public Zmogus {
private:
    string vardas = "A", pavarde = "BB";
    vector<int> paz;
    int egz = 0;
    double rez = 0.0;
    double medrez = 0.0;

public:
    Studentas() = default;

// Rule of Five
~Studentas() = default;

Studentas(const Studentas& other)
    : vardas(other.vardas),
      pavarde(other.pavarde),
      paz(other.paz),
      egz(other.egz),
      rez(other.rez),
      medrez(other.medrez)
{}

Studentas& operator=(const Studentas& other) {
    if (this != &other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        paz = other.paz;
        egz = other.egz;
        rez = other.rez;
        medrez = other.medrez;
    }
    return *this;
}

Studentas(Studentas&& other) noexcept
    : vardas(std::move(other.vardas)),
      pavarde(std::move(other.pavarde)),
      paz(std::move(other.paz)),
      egz(other.egz),
      rez(other.rez),
      medrez(other.medrez)
{
    other.egz = 0;
    other.rez = 0;
    other.medrez = 0;
}

Studentas& operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas = std::move(other.vardas);
        pavarde = std::move(other.pavarde);
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


    string& refVardas() { return vardas; }
    string& refPavarde() { return pavarde; }
    vector<int>& refPaz() { return paz; }
    int& refEgz() { return egz; }
    double& refRez() { return rez; }
    double& refMedrez() { return medrez; }
    void clearPaz() { paz.clear(); }

    // getteriai
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }
    double getRez() const { return rez; }
    double getMedrez() const { return medrez; }
    int getEgz() const { return egz; }
    vector<int>& getPaz() { return paz; }

    // setteriai
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }
    void addPaz(int p) { paz.push_back(p); }
    void setEgz(int e) { egz = e; }

    void skaiciuoti();
};

const string irasymo_failas = "kursiokai.txt";
const string irasymo_failas_geras = "kursiokai_geri.txt";
const string irasymo_failas_blogas = "kursiokai_blogi.txt";

void inputas(vector<Studentas> &grupe);
void failinputas(vector<Studentas> &grupe, string reading);
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const vector<Studentas> &grupe);
void failoutputas(const vector<Studentas> &grupe, string writing);
void failgeneravimas();
void genirasymas(vector<Studentas> &grupe, vector<Studentas> &protingi, vector<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);
void rikiuoti(vector<Studentas> &grupe, int pasirinkimas);
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);
void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi);
void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t);
void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi);
void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi);

ostream& operator<<(ostream& os, const Studentas& s);
istream& operator>>(istream& is, Studentas& s);


#endif
