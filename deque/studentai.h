#ifndef STUDENTAI_H
#define STUDENTAI_H

using namespace std;

const deque<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const deque<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
const deque<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
const deque<string> mgalunes = {"as", "aitis"};
const deque<string> fgalunes = {"iene", "aite", "yte"};

struct Studentas {
    string vardas = "A", pavarde = "BB";
    deque<int> paz;
    int egz;
    double rez;
    double medrez;
};

const string irasymo_failas = "kursiokai.txt";
const string irasymo_failas_geras = "kursiokai_geri.txt";
const string irasymo_failas_blogas = "kursiokai_blogi.txt";

void inputas(deque<Studentas> &grupe);
void failinputas(deque<Studentas> &grupe, string reading);
void randominputas(deque<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const deque<Studentas> &grupe);
void failoutputas(const deque<Studentas> &grupe, string writing);
void failgeneravimas();
void genirasymas(deque<Studentas> &grupe, deque<Studentas> &protingi, deque<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);
void rikiuoti(deque<Studentas> &grupe, int pasirinkimas);
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);
void skirstyti(const deque<Studentas>& grupe, deque<Studentas>& protingi, deque<Studentas>& neprotingi);
void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t);
                
#endif