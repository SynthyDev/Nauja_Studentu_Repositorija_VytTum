#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include "studentai.h"
#include <stdexcept>
#include "Vector.h"

using namespace std;

void Studentas::skaiciuoti() //! apskaičiuoja galutinius medianinius ir vidurkinius studento rezultatus
{
    //! Compute final average and median-based results
    if (paz.empty()) return;

    int sum = 0;
    for (int x : paz) sum += x;

    rez = 0.4 * (sum * 1.0 / paz.size()) + 0.6 * egz;

    vector<int> temp = paz;
    sort(temp.begin(), temp.end());

    if (temp.size() % 2 == 0)
        medrez = (temp[temp.size()/2 - 1] + temp[temp.size()/2]) / 2.0;
    else
        medrez = temp[temp.size()/2];

    medrez = medrez * 0.4 + egz * 0.6;
}

void inputas(vector<Studentas> &grupe) //! rankinė studentų įvestis
{
    Studentas A;

    while (true)
    {
        int sum = 0;

        cout << "Vardas ir pavarde: ";
        cin >> A.refVardas() >> A.refPavarde();

        int i = 0;
        string ats;
        while (true)
        {
            int temp;
            cout << "Iveskite pazymi numeris " << i + 1 << ": ";
            try
            {
                cin >> temp;
                if (cin.fail())
                    throw runtime_error("Bloga ivestis.");
            }
            catch (exception& e)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << e.what() << " Bandykite dar karta.\n";
                continue;
            }

            A.refPaz().push_back(temp);
            sum += temp;

            cout << "Ar toliau vesite pazymius? (y/n): ";
            cin >> ats;
            if (ats == "n") break;
            else if (ats == "y") cout << "Veskite toliau: ";

            i++;
        }

        cout << "Iveskite egzamino rezultata: ";
        try
        {
            cin >> A.refEgz();
            if (cin.fail())
                throw runtime_error("Bloga ivestis.");
        }
        catch (exception& e)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << e.what() << " Bandykite dar karta.\n";
            continue;
        }

        if (!A.refPaz().empty())
        {
            A.refRez() = (sum * 1.0 / A.refPaz().size()) * 0.4 + A.refEgz() * 0.6;

            sort(A.refPaz().begin(), A.refPaz().end());

            int n = A.refPaz().size();
            if (n % 2 == 0)
                A.refMedrez() = (A.refPaz()[n/2 - 1] + A.refPaz()[n/2]) / 2.0;
            else
                A.refMedrez() = A.refPaz()[n/2];

            A.refMedrez() = A.refMedrez() * 0.4 + A.refEgz() * 0.6;
            A.skaiciuoti();
        }

        grupe.push_back(A);
        A.clearPaz();

        cout << "Ar toliau vesite mokinius? (y/n): ";
        cin >> ats;
        if (ats == "n") break;
    }
}

void outputas(const vector<Studentas> &grupe) //! atspausdina studentus į console
{
    //! Print students to console
    cout << "-------------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(20) << "Rezultatas (Vid.) /"
         << setw(20) << " Rezultatas (Med.)"
         << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (const auto &A : grupe)
    {
        cout << left << setw(20) << A.getVardas()
             << setw(20) << A.getPavarde()
             << right << setw(20) << fixed << setprecision(2) << A.getRez()
             << setw(20) << A.getMedrez()
             << endl;
    }
}

void failoutputas(const vector<Studentas> &grupe, string writing) //! studentų spausdinimas į failą (be rikiavimo)
{
    //! Write students to file
    ofstream out(writing);
    out << "------------------------------------------------------------------- \n";
    out << left << setw(20) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(20) << "Rezultatas (Vid.) /"
        << setw(20) << " Rezultatas (Med.)"
        << "\n";
    out << "------------------------------------------------------------------- \n";

    for (const Studentas& s : grupe)
    {
        out << left << setw(20) << s.getVardas()
            << setw(20) << s.getPavarde()
            << fixed << setprecision(2)
            << setw(20) << s.getRez()
            << setw(20) << s.getMedrez()
            << '\n';
    }

    cout << "Studentu skaicius: " << grupe.size() << endl;
}

void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus) //! atsitiktinių studentų generavimas
{
    Studentas A;
    string lytis;
    string ats;

    if (ArGeneruotiVardus)
    {
        int zmonsk = rand() % 100 + 1;

        for(int iii = 0; iii < zmonsk; iii++)
        {
            int sum = 0;

            lytis = lytgen();
            A.refVardas() = randomvardas(lytis);
            A.refPavarde() = randompavarde(lytis);

            int pazsk = rand() % 100 + 1;

            for (int ii = 0; ii < pazsk; ii++)
            {
                int temp = rand() % 10 + 1;
                A.refPaz().push_back(temp);
                sum += temp;
            }

            A.refEgz() = rand() % 10 + 1;

            if (!A.refPaz().empty())
            {
                A.refRez() = (sum * 1.0 / A.refPaz().size()) * 0.4 + A.refEgz() * 0.6;

                sort(A.refPaz().begin(), A.refPaz().end());

                int n = A.refPaz().size();
                if (n % 2 == 0)
                    A.refMedrez() = (A.refPaz()[n/2 - 1] + A.refPaz()[n/2]) / 2.0;
                else
                    A.refMedrez() = A.refPaz()[n/2];

                A.refMedrez() = A.refMedrez() * 0.4 + A.refEgz() * 0.6;
            }

            grupe.push_back(A);
            A.clearPaz();
        }
    }
    else
    {
        while (true)
        {
            int sum = 0;

            cout << "Vardas ir pavarde: ";
            cin >> A.refVardas() >> A.refPavarde();

            int pazsk = rand() % 100 + 1;

            for (int i = 0; i < pazsk; i++)
            {
                int temp = rand() % 10 + 1;
                A.refPaz().push_back(temp);
                sum += temp;
            }

            A.refEgz() = rand() % 10 + 1;

            if (!A.refPaz().empty())
            {
                A.refRez() = (sum * 1.0 / A.refPaz().size()) * 0.4 + A.refEgz() * 0.6;

                sort(A.refPaz().begin(), A.refPaz().end());

                int n = A.refPaz().size();
                if (n % 2 == 0)
                    A.refMedrez() = (A.refPaz()[n/2 - 1] + A.refPaz()[n/2]) / 2.0;
                else
                    A.refMedrez() = A.refPaz()[n/2];

                A.refMedrez() = A.refMedrez() * 0.4 + A.refEgz() * 0.6;
            }

            grupe.push_back(A);
            A.clearPaz();

            cout << "Ar toliau vesite zmones? (y/n): ";
            cin >> ats;
            if (ats == "n") break;
        }
    }
}

void failinputas(vector<Studentas> &grupe, string reading) //! studentų nuskaitymas iš failo
{
    ifstream file(reading);
    grupe.reserve(1000000);

    if (!file)
    {
        cout << "Nepavyko atidaryti failo\n";
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        istringstream iss(line);

        Studentas A;

        iss >> A.refVardas() >> A.refPavarde();

        int pazymys;

        while (iss >> pazymys)
            A.refPaz().push_back(pazymys);

        if (!A.refPaz().empty())
        {
            A.refEgz() = A.refPaz().back();
            A.refPaz().pop_back();
        }

        if (!A.refPaz().empty())
        {
            int sum = 0;
            for (int x : A.refPaz())
                sum += x;

            sort(A.refPaz().begin(), A.refPaz().end());

            int n = A.refPaz().size();

            if (n % 2 == 0)
                A.refMedrez() = (A.refPaz()[n/2 - 1] + A.refPaz()[n/2]) / 2.0;
            else
                A.refMedrez() = A.refPaz()[n/2];

            A.refMedrez() = A.refMedrez() * 0.4 + A.refEgz() * 0.6;
            A.refRez() = 0.4 * (sum * 1.0 / A.refPaz().size()) + 0.6 * A.refEgz();
        }

        grupe.push_back(A);
    }
}


string randomvardas(string lytis) //! random vardo generavimas iš listo
{
    if (lytis == "mot")
        return fvardai[rand() % fvardai.size()];
    else
        return mvardai[rand() % mvardai.size()];
}

string randompavarde(string lytis) //! random pavardės generavimas iš listo
{
    int index = rand() % pavardes.size();
    string galune;

    if (lytis == "mot")
        galune = fgalunes[rand() % fgalunes.size()];
    else
        galune = mgalunes[rand() % mgalunes.size()];

    return pavardes[index] + galune;
}

string lytgen() //! random lyties generavimas
{
    return rand() % 2 == 0 ? "vyr" : "mot";
}


bool cmpVardas(const Studentas &a, const Studentas &b) //! vardo palyginimas
{
    return a.getVardas() < b.getVardas();
}

bool cmpPavarde(const Studentas &a, const Studentas &b) //! pavardės palyginimas
{
    return a.getPavarde() < b.getPavarde();
}

bool cmpRez(const Studentas &a, const Studentas &b) //! rezultatų palyginimas
{
    return a.getRez() < b.getRez();
}

bool cmpMedrez(const Studentas &a, const Studentas &b) //! medianos rezultatų palyginimas
{
    return a.getMedrez() < b.getMedrez();
}

bool cmpEgz(const Studentas &a, const Studentas &b) //! egzamino rezultatų palyginimas
{
    return a.getEgz() < b.getEgz();
}


void rikiuoti(vector<Studentas> &grupe, int pasirinkimas) //! studentų rikiavimas pagal cmp funkcijas
{
    if (pasirinkimas == 1)
        sort(grupe.begin(), grupe.end(), cmpVardas);
    else if (pasirinkimas == 2)
        sort(grupe.begin(), grupe.end(), cmpPavarde);
    else if (pasirinkimas == 3)
        sort(grupe.begin(), grupe.end(), cmpRez);
    else if (pasirinkimas == 4)
        sort(grupe.begin(), grupe.end(), cmpMedrez);
    else if (pasirinkimas == 5)
        sort(grupe.begin(), grupe.end(), cmpEgz);
}


void failgeneravimas() //! generuoja 5 failus su atsitiktiniais studentais
{
    int sk = 1000;
    for (int it = 0; it < 5; it++)
    {
        cout << "pradedamas " << sk << " eiluciu failo generavimo laiko skaiciavimas" << endl;
        auto input_start = chrono::high_resolution_clock::now();
        
        ofstream gen("gen" + to_string(sk) + ".txt");
        gen << left << setw(20) << "STUD. VARDAS"
            << setw(20) << "STUD. PAVARDE"
            << setw(20) << "STUD PAZYMIAI (PASKUTINIS EGZAMINO)\n";

        for (int genit = 1; genit <= sk; genit++)
        {
            gen << left << setw(20) << "genVardas" + to_string(genit)
                << setw(20) << "genPavarde" + to_string(genit);

            for (int i = 1; i <= 16; i++)
                gen << setw(20) << rand() % 10 + 1;

            gen << "\n";
        }

        gen.close();
        sk *= 10;

        auto input_end = chrono::high_resolution_clock::now();
        chrono::duration<double> input_diff = input_end - input_start;
        cout << "Failu sukurimas + uzdarymas uztruko: " << input_diff.count() << " s \n";
    }
}


void genirasymas(vector<Studentas> &grupe, vector<Studentas> &protingi, vector<Studentas> &neprotingi, 
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija) //! skaito gen failus iš failgeneravimas funkcijos, rikiuoja ir paskirsto į naujus failus
{
    int sk = 1000;

    for (int it = 0; it < 5; it++)
    {
        string filename = "gen" + to_string(sk) + ".txt";

        cout << "Pradedamas failo nuskaitymas: " << filename << endl;
        auto start_read = chrono::high_resolution_clock::now();

        ifstream file(filename);

        if (!file)
        {
            cout << "Nepavyko atidaryti failo\n";
            sk *= 10;
            continue;
        }

        string line;

        getline(file, line); // skip header

        while (getline(file, line))
        {
            istringstream iss(line);

            Studentas A;

            iss >> A.refVardas() >> A.refPavarde();

            int paz;
            while (iss >> paz)
                A.refPaz().push_back(paz);

            if (A.refPaz().empty())
                continue;

            A.refEgz() = A.refPaz().back();
            A.refPaz().pop_back();

            int sum = 0;
            for (int x : A.refPaz())
                sum += x;

            A.refRez() = 0.4 * (sum * 1.0 / A.refPaz().size()) + 0.6 * A.refEgz();

            sort(A.refPaz().begin(), A.refPaz().end());

            int n = A.refPaz().size();

            if (n % 2 == 0)
                A.refMedrez() = (A.refPaz()[n/2 - 1] + A.refPaz()[n/2]) / 2.0;
            else
                A.refMedrez() = A.refPaz()[n/2];

            A.refMedrez() = A.refMedrez() * 0.4 + A.refEgz() * 0.6;

            grupe.push_back(A);
        }

        file.close();

        auto end_read = chrono::high_resolution_clock::now();
        chrono::duration<double> diff_read = end_read - start_read;

        cout << "Failo nuskaitymas uztruko: " << diff_read.count() << " s\n";

        auto start_rikiavimas = chrono::high_resolution_clock::now();
        rikiuoti(grupe, rik_pasirinkimas);
        auto end_rikiavimas = chrono::high_resolution_clock::now();
        chrono::duration<double> diff_rikiavimas = end_rikiavimas - start_rikiavimas;

        cout << "Rikiavimas failui " << filename << " uztruko: " << diff_rikiavimas.count() << " s\n";

        auto start_skirstymas = chrono::high_resolution_clock::now();

        if (strategija == SkirstymoStrategija::PIRMAS)
            skirstyti(grupe, protingi, neprotingi);
        else if (strategija == SkirstymoStrategija::ANTRAS)
            skirstyti2(grupe, neprotingi);
        else if (strategija == SkirstymoStrategija::TRECIAS)
            skirstyti3(grupe, neprotingi);

        auto end_skirstymas = chrono::high_resolution_clock::now();
        chrono::duration<double> diff_skirstymas = end_skirstymas - start_skirstymas;

        cout << "Protingu/Neprotingu skirstymas failui " << filename << " uztruko: " << diff_skirstymas.count() << " s\n";

        if (strategija == SkirstymoStrategija::PIRMAS)
        {
            cout << "Protingu ";
            failoutputas(protingi, "kursiokai_geri_" + to_string(sk) + ".txt");
            cout << "Neprotingu ";
            failoutputas(neprotingi, "kursiokai_blogi_" + to_string(sk) + ".txt");
        }
        else
        {
            cout << "Protingu ";
            failoutputas(grupe, "kursiokai_geri_" + to_string(sk) + ".txt");
            cout << "Neprotingu ";
            failoutputas(neprotingi, "kursiokai_blogi_" + to_string(sk) + ".txt");
        }

        cout << "\n";

        grupe.clear();
        protingi.clear();
        neprotingi.clear();

        logResults(
            "vector",
            sk,
            diff_read.count(),
            diff_rikiavimas.count(),
            diff_skirstymas.count()
        );

        sk *= 10;
    }
}


void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi) //! studentų skirstymas į grupes pagal rezultatus
{
    for (const auto& s : grupe)
    {
        if (s.getRez() >= 5.0)
            protingi.push_back(s);
        else
            neprotingi.push_back(s);
    }
}


void logResults(const string& container, int size,
                double read_t, double sort_t, double split_t)
{
    ofstream out("results.csv", ios::app);
    out << container << ","
        << size << ","
        << read_t << ","
        << sort_t << ","
        << split_t << "\n";
}


void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi) //! studentų skirstymas antra taktika
{
    auto it = partition(grupe.begin(), grupe.end(),
        [](const Studentas& s) { return s.getRez() >= 5.0; });

    neprotingi.assign(it, grupe.end());
    grupe.erase(it, grupe.end());
}


void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi) //! studentų skirstymas trečia taktika
{
    neprotingi.reserve(grupe.size());

    auto it = remove_if(grupe.begin(), grupe.end(),
        [&](const Studentas& s)
        {
            if (s.getRez() < 5.0)
            {
                neprotingi.push_back(s);
                return true;
            }
            return false;
        });

    grupe.erase(it, grupe.end());
}

ostream& operator<<(ostream& os, const Studentas& s) //! output operatorius klasei
{
    os << left << setw(20) << s.getVardas()
       << setw(20) << s.getPavarde()
       << setw(10) << fixed << setprecision(2) << s.getRez()
       << setw(10) << s.getMedrez();
    return os;
}

istream& operator>>(istream& is, Studentas& s) //! input operatorius klasei
{
    s.refPaz().clear();

    is >> s.refVardas() >> s.refPavarde();

    int paz;
    while (is >> paz) {
        s.refPaz().push_back(paz);
    }

    if (!s.refPaz().empty()) {
        s.refEgz() = s.refPaz().back();
        s.refPaz().pop_back();
        s.skaiciuoti();
    }

    return is;
}
