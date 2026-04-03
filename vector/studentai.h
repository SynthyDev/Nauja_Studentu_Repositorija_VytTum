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

class Studentas {
private:
    string vardas_ = "A";
    string pavarde_ = "BB";
    vector<int> paz_;
    int egz_ = 0;

    double rez_ = 0.0;
    double medrez_ = 0.0;

    void skaiciuoti();

public:
    // konstruktorius
    Studentas() = default;

    // getteriai
    string vardas() const { return vardas_; }
    string pavarde() const { return pavarde_; }
    double rez() const { return rez_; }
    double medrez() const { return medrez_; }
    int egz() const { return egz_; }
    const vector<int>& paz() const { return paz_; }

    // setteriai
    void setVardas(const string& v) { vardas_ = v; }
    void setPavarde(const string& p) { pavarde_ = p; }
    void addPaz(int p) { paz_.push_back(p); }
    void setEgz(int e) { egz_ = e; }

    void skaiciuotiGalutini();
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
#endif