#ifndef STUDENTAI_H
#define STUDENTAI_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//! Male first names for random generation
const vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
//! Female first names for random generation
const vector<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
//! Base surname stems
const vector<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
//! Male surname endings
const vector<string> mgalunes = {"as", "aitis"};
//! Female surname endings
const vector<string> fgalunes = {"iene", "aite", "yte"};

//! Strategies for splitting students into groups
enum class SkirstymoStrategija
{
    PIRMAS,   //! Simple push_back into two vectors
    ANTRAS,   //! Using std::partition
    TRECIAS   //! Using std::remove_if
};

class Zmogus {
protected:
    string vardas;  //! First name
    string pavarde; //! Last name

public:
    virtual ~Zmogus() = default;

    virtual void info() const = 0; //! Abstract info printer

    string& refVardas() { return vardas; } //! Reference to first name
    string& refPavarde() { return pavarde; } //! Reference to last name
    string getVardas() const { return vardas; } //! Get first name
    string getPavarde() const { return pavarde; } //! Get last name
    void setVardas(const string& v) { vardas = v; } //! Set first name
    void setPavarde(const string& p) { pavarde = p; } //! Set last name
};


class Studentas : public Zmogus {
private:
    vector<int> paz;   //! Homework grades
    int egz = 0;       //! Exam grade
    double rez = 0.0;  //! Final average result
    double medrez = 0.0; //! Final median result

public:
    Studentas() = default;

    // Rule of Five
    ~Studentas() = default; //! Destructor

    Studentas(const Studentas& other)
        : Zmogus(other),
          paz(other.paz),
          egz(other.egz),
          rez(other.rez),
          medrez(other.medrez)
    {} //! Copy constructor

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            paz = other.paz;
            egz = other.egz;
            rez = other.rez;
            medrez = other.medrez;
        }
        return *this;
    } //! Copy assignment

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
    } //! Move constructor

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
    } //! Move assignment

    void info() const override { // kad veiktu ne abstrakciai?
        cout << "Studentas: " << vardas << " " << pavarde << endl;
    } //! Print student info

    vector<int>& refPaz() { return paz; } //! Reference to grade vector
    int& refEgz() { return egz; } //! Reference to exam grade
    double& refRez() { return rez; } //! Reference to final average
    double& refMedrez() { return medrez; } //! Reference to final median
    void clearPaz() { paz.clear(); } //! Clear homework grades
    double getRez() const { return rez; } //! Get final average
    double getMedrez() const { return medrez; } //! Get final median
    int getEgz() const { return egz; } //! Get exam grade

    vector<int>& getPaz() { return paz; } //! Get grade vector

    void addPaz(int p) { paz.push_back(p); } //! Add homework grade
    void setEgz(int e) { egz = e; } //! Set exam grade

    void skaiciuoti(); //! Compute final results
};

//! Default output filenames
const string irasymo_failas = "kursiokai.txt";
const string irasymo_failas_geras = "kursiokai_geri.txt";
const string irasymo_failas_blogas = "kursiokai_blogi.txt";

void inputas(vector<Studentas> &grupe); //! Manual input
void failinputas(vector<Studentas> &grupe, string reading); //! Read from file
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus); //! Random generation
void outputas(const vector<Studentas> &grupe); //! Print to console
void failoutputas(const vector<Studentas> &grupe, string writing); //! Print to file
void failgeneravimas(); //! Generate test files
void genirasymas(vector<Studentas> &grupe, vector<Studentas> &protingi, vector<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija); //! Process generated files
string lytgen(); //! Random gender
string randomvardas(string lytis); //! Random first name
string randompavarde(string lytis); //! Random surname
void rikiuoti(vector<Studentas> &grupe, int pasirinkimas); //! Sort students
bool cmpVardas(const Studentas &a, const Studentas &b); //! Compare by first name
bool cmpPavarde(const Studentas &a, const Studentas &b); //! Compare by last name
bool cmpRez(const Studentas &a, const Studentas &b); //! Compare by final average
bool cmpMedrez(const Studentas &a, const Studentas &b); //! Compare by final median
bool cmpEgz(const Studentas &a, const Studentas &b); //! Compare by exam
void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi); //! Split method 1
void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t); //! Log timings
void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi); //! Split using partition
void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi); //! Split using remove_if

ostream& operator<<(ostream& os, const Studentas& s); //! Output operator
istream& operator>>(istream& is, Studentas& s); //! Input operator

#endif
