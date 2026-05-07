#ifndef STUDENTAI_H
#define STUDENTAI_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//! Male first names used for random generation
const vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
//! Female first names used for random generation
const vector<string> fvardai = {"Egle", "Viktorija", "Vakare", "Inga", "Ema", "Marija", "Janina"};
//! Base surnames used for random generation
const vector<string> pavardes = {"Macerausk", "Jankausk", "Kazlausk", "Svilpausk", "Drugeliausk", "Briedausk"};
//! Male surname endings
const vector<string> mgalunes = {"as", "aitis"};
//! Female surname endings
const vector<string> fgalunes = {"iene", "aite", "yte"};

//! Strategies for splitting students into groups
enum class SkirstymoStrategija
{
    PIRMAS,   //!< Simple push into two vectors
    ANTRAS,   //!< Using partition
    TRECIAS   //!< Using remove_if
};

//! Abstract base class representing a person
class Zmogus {
protected:
    string vardas;   //!< First name
    string pavarde;  //!< Last name

public:
    virtual ~Zmogus() = default;

    //! Print basic info (implemented in derived classes)
    virtual void info() const = 0;

    //! Reference to first name
    string& refVardas() { return vardas; }
    //! Reference to last name
    string& refPavarde() { return pavarde; }

    //! Get first name
    string getVardas() const { return vardas; }
    //! Get last name
    string getPavarde() const { return pavarde; }

    //! Set first name
    void setVardas(const string& v) { vardas = v; }
    //! Set last name
    void setPavarde(const string& p) { pavarde = p; }
};


//! Student class storing grades, exam, and results
class Studentas : public Zmogus {
private:
    vector<int> paz;   //!< Homework grades
    int egz = 0;       //!< Exam grade
    double rez = 0.0;  //!< Final average result
    double medrez = 0.0; //!< Final median result

public:
    Studentas() = default;

    //! Destructor (Rule of Five)
    ~Studentas() = default;

    //! Copy constructor
    Studentas(const Studentas& other)
        : Zmogus(other),
          paz(other.paz),
          egz(other.egz),
          rez(other.rez),
          medrez(other.medrez)
    {}

    //! Copy assignment
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

    //! Move constructor
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

    //! Move assignment
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

    //! Print student info
    void info() const override {
        cout << "Studentas: " << vardas << " " << pavarde << endl;
    }

    //! Reference to grade vector
    vector<int>& refPaz() { return paz; }
    //! Reference to exam grade
    int& refEgz() { return egz; }
    //! Reference to final average
    double& refRez() { return rez; }
    //! Reference to final median
    double& refMedrez() { return medrez; }

    //! Clear homework grades
    void clearPaz() { paz.clear(); }

    //! Get final average
    double getRez() const { return rez; }
    //! Get final median
    double getMedrez() const { return medrez; }
    //! Get exam grade
    int getEgz() const { return egz; }

    //! Get grade vector
    vector<int>& getPaz() { return paz; }

    //! Add a homework grade
    void addPaz(int p) { paz.push_back(p); }

    //! Set exam grade
    void setEgz(int e) { egz = e; }

    //! Compute final results
    void skaiciuoti();
};

//! Default output filenames
const string irasymo_failas = "kursiokai.txt";
const string irasymo_failas_geras = "kursiokai_geri.txt";
const string irasymo_failas_blogas = "kursiokai_blogi.txt";

//! Manual input
void inputas(vector<Studentas> &grupe);
//! Read from file
void failinputas(vector<Studentas> &grupe, string reading);
//! Random generation
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus);
//! Print to console
void outputas(const vector<Studentas> &grupe);
//! Print to file
void failoutputas(const vector<Studentas> &grupe, string writing);
//! Generate test files
void failgeneravimas();

//! Read, sort, split, and write generated files
void genirasymas(vector<Studentas> &grupe, vector<Studentas> &protingi, vector<Studentas> &neprotingi,
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija);

//! Generate random gender
string lytgen();
//! Generate random first name
string randomvardas(string lytis);
//! Generate random surname
string randompavarde(string lytis);

//! Sort students
void rikiuoti(vector<Studentas> &grupe, int pasirinkimas);

//! Comparators
bool cmpVardas(const Studentas &a, const Studentas &b);
bool cmpPavarde(const Studentas &a, const Studentas &b);
bool cmpRez(const Studentas &a, const Studentas &b);
bool cmpMedrez(const Studentas &a, const Studentas &b);
bool cmpEgz(const Studentas &a, const Studentas &b);

//! Simple split into two groups
void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi);
//! Log timing results
void logResults(const string& container, int size, double read_t, double sort_t, double split_t);
//! Split using partition
void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi);
//! Split using remove_if
void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi);

//! Output operator
ostream& operator<<(ostream& os, const Studentas& s);
//! Input operator
istream& operator>>(istream& is, Studentas& s);

#endif
