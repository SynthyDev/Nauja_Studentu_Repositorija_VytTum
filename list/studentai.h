#ifndef STUDENTAI_H
#define STUDENTAI_H

using namespace std;

const vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const vector<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
const vector<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
const vector<string> mgalunes = {"as", "aitis"};
const vector<string> fgalunes = {"iene", "aite", "yte"};

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

void inputas(list<Studentas> &grupe);
void failinputas(list<Studentas> &grupe, string reading);
void randominputas(list<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const list<Studentas> &grupe);
void failoutputas(const list<Studentas> &grupe, string writing);
void failgeneravimas();
void genirasymas(list<Studentas> &grupe, list<Studentas> &protingi, list<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);
void rikiuoti(list<Studentas> &grupe, int pasirinkimas);
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);
void skirstyti(const list<Studentas>& grupe, list<Studentas>& protingi, list<Studentas>& neprotingi);
void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t);
                
#endif