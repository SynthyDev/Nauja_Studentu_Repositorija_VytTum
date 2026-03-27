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
    ANTRAS
};

struct Studentas {
    string vardas = "A", pavarde = "BB";
    vector<int> paz;
    int egz;
    double rez;
    double medrez;
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

#endif