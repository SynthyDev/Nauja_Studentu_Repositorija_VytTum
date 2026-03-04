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

// system("dir *.txt") ??
const string skaitymo_failas = "studentai10000.txt";
const string irasymo_failas = "kursiokai.txt";

void inputas(vector<Studentas> &grupe);
void failinputas(vector<Studentas> &grupe, string reading);
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const vector<Studentas> &grupe);
void failoutputas(const vector<Studentas> &grupe, string writing);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);
void rikiuoti(vector<Studentas> &grupe, int pasirinkimas);
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);

#endif