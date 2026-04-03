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

using namespace std;

// ===== CLASS METHOD =====
void Studentas::skaiciuoti()
{
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

// ===== INPUT =====
void inputas(vector<Studentas> &grupe)
{
    Studentas A;
    
    while (true)
    {
        cout << "Vardas ir pavarde: ";
        string v, p;
        cin >> v >> p;
        A.setVardas(v);
        A.setPavarde(p);

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

            A.addPaz(temp);

            cout << "Ar toliau vesite pazymius? (y/n): ";
            cin >> ats;
            if (ats == "n") break;
            else if (ats == "y") cout << "Veskite toliau: ";

            i++;
        }

        cout << "Iveskite egzamino rezultata: ";
        int egz;
        cin >> egz;
        A.setEgz(egz);

        A.skaiciuoti();

        grupe.push_back(A);
        A.getPaz().clear();

        cout << "Ar toliau vesite mokinius? (y/n): ";
        cin >> ats;
        if (ats == "n") break;
    }
}

// ===== OUTPUT =====
void outputas(const vector<Studentas> &grupe)
{
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

    cout << "-------------------------------------------------------------------" << endl;
}

// ===== FILE OUTPUT =====
void failoutputas(const vector<Studentas> &grupe, string writing)
{
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
            << setw(20) << s.getMedrez() << '\n';
    }

    cout << "Studentu skaicius: " << grupe.size() << endl;
}

// ===== RANDOM INPUT =====
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus)
{
    Studentas A;
    
    string lytis;

    int zmonsk = rand() % 100 + 1;

    for(int iii = 0; iii < zmonsk; iii++)
    {
        lytis = lytgen();
        A.setVardas(randomvardas(lytis));
        A.setPavarde(randompavarde(lytis));

        int pazsk = rand() % 100 + 1;

        for (int ii = 0; ii < pazsk; ii++)
        {
            int temp = rand() % 10 + 1;
            A.addPaz(temp);
        }

        A.setEgz(rand() % 10 + 1);
        A.skaiciuoti();

        grupe.push_back(A);
        A.getPaz().clear();
    }
}

// ===== FILE INPUT =====
void failinputas(vector<Studentas> &grupe, string reading)
{
    ifstream file(reading);
    grupe.reserve(1000000);

    if (!file) {
        cout << "Nepavyko atidaryti failo\n";
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        istringstream iss(line);

        Studentas A;

        string v, p;
        iss >> v >> p;
        A.setVardas(v);
        A.setPavarde(p);

        int pazymys;
        vector<int> temp;

        while (iss >> pazymys)
            temp.push_back(pazymys);

        if (!temp.empty())
        {
            A.setEgz(temp.back());
            temp.pop_back();

            for (int x : temp)
                A.addPaz(x);
        }

        A.skaiciuoti();
        grupe.push_back(A);
    }
}

// ===== RANDOM HELPERS =====
string randomvardas(string lytis)
{
    if (lytis == "mot")
        return fvardai[rand() % fvardai.size()];
    else
        return mvardai[rand() % mvardai.size()];
}

string randompavarde(string lytis)
{
    int index = rand() % pavardes.size();
    string galune;

    if (lytis == "mot")
        galune = fgalunes[rand() % fgalunes.size()];
    else
        galune = mgalunes[rand() % mgalunes.size()];

    return pavardes[index] + galune;
}

string lytgen()
{
    return rand() % 2 == 0 ? "vyr" : "mot";
}

// ===== SORT =====
bool cmpVardas(const Studentas &a, const Studentas &b)
{
    return a.getVardas() < b.getVardas();
}

bool cmpPavarde(const Studentas &a, const Studentas &b)
{
    return a.getPavarde() < b.getPavarde();
}

bool cmpRez(const Studentas &a, const Studentas &b)
{
    return a.getRez() < b.getRez();
}

bool cmpMedrez(const Studentas &a, const Studentas &b)
{
    return a.getMedrez() < b.getMedrez();
}

bool cmpEgz(const Studentas &a, const Studentas &b)
{
    return a.getEgz() < b.getEgz();
}

void rikiuoti(vector<Studentas> &grupe, int pasirinkimas)
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

// ===== FILE GENERATION =====
void failgeneravimas()
{
    int sk = 1000;
    for (int it = 0; it < 5; it++)
    {
        cout << "pradedamas " << sk <<" eiluciu failo generavimo laiko skaiciavimas" << endl;
        auto input_start = chrono::high_resolution_clock::now();
        
        ofstream gen;
        gen.open("gen" + to_string(sk) + ".txt");
        gen << left << setw(20) << "STUD. VARDAS"
            << setw(20) << "STUD. PAVARDE"
            << setw(20) << "PAZYMIAI (PASKUTINIS EGZAMINO)\n";

        for (int genit = 1; genit <= sk; genit++)
        {
            gen << left << setw(20) << "genVardas" + to_string(genit)
                << setw(20) << "genPavarde" + to_string(genit);

            for (int i = 1; i <= 16; i++)
                gen << setw(5) << rand() % 10 + 1;

            gen << "\n";
        }

        gen.close();
        sk *= 10;

        auto input_end = chrono::high_resolution_clock::now();
        chrono::duration<double> input_diff = input_end - input_start;
        cout << "Failu sukurimas + uzdarymas uztruko: " << input_diff.count() << " s \n";
    }
}

// ===== SPLIT =====
void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi)
{
    for (const auto& s : grupe)
    {
        if (s.getRez() >= 5.0)
            protingi.push_back(s);
        else
            neprotingi.push_back(s);
    }
}

void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi)
{
    auto it = partition(grupe.begin(), grupe.end(),
        [](const Studentas& s) { return s.getRez() >= 5.0; });

    neprotingi.assign(it, grupe.end());
    grupe.erase(it, grupe.end());
}

void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi)
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

// ===== GEN + STRATEGY =====
void genirasymas(vector<Studentas> &grupe, vector<Studentas> &protingi, vector<Studentas> &neprotingi, 
    string writing_good, string writing_bad, int rik_pasirinkimas, SkirstymoStrategija strategija)
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
        getline(file, line);

        while (getline(file, line))
        {
            istringstream iss(line);

            Studentas A;

            string v, p;
            iss >> v >> p;
            A.setVardas(v);
            A.setPavarde(p);

            int paz;
            vector<int> temp;

            while (iss >> paz)
                temp.push_back(paz);

            if (temp.empty()) continue;

            A.setEgz(temp.back());
            temp.pop_back();

            for (int x : temp)
                A.addPaz(x);

            A.skaiciuoti();
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

        cout << "Rikiavimas uztruko: " << diff_rikiavimas.count() << " s\n";

        auto start_skirstymas = chrono::high_resolution_clock::now();

        if (strategija == SkirstymoStrategija::PIRMAS)
            skirstyti(grupe, protingi, neprotingi);
        else if (strategija == SkirstymoStrategija::ANTRAS)
            skirstyti2(grupe, neprotingi);
        else
            skirstyti3(grupe, neprotingi);

        auto end_skirstymas = chrono::high_resolution_clock::now();
        chrono::duration<double> diff_skirstymas = end_skirstymas - start_skirstymas;

        cout << "Skirstymas uztruko: " << diff_skirstymas.count() << " s\n";

        grupe.clear();
        protingi.clear();
        neprotingi.clear();

        logResults("vector", sk, diff_read.count(), diff_rikiavimas.count(), diff_skirstymas.count());

        sk *= 10;
    }
}

// ===== LOG =====
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