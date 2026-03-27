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

void inputas(vector<Studentas> &grupe)
{
    Studentas A;
    
    while (true)
    {
        int sum = 0;

        cout << "Vardas ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

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

            A.paz.push_back(temp);
            sum += temp;

            cout << "Ar toliau vesite pazymius? (y/n): ";
            cin >> ats;
            if (ats == "n")
            {
                break;
            }
            else if (ats == "y")
            {
                cout << "Veskite toliau: ";
            }
            else
            {
                cout << "NETEISINGA IVESTIS, programa veikia toliau" << endl;
            }

            i++;
        }

        cout << "Iveskite egzamino rezultata: ";
        try
        {
            cin >> A.egz;
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

        if (A.paz.size() > 0)
        {
            A.rez = (sum * 1.0 / A.paz.size()) * 0.4 + A.egz * 0.6;

            sort(A.paz.begin(), A.paz.end());

            int n = A.paz.size();
            if (n % 2 == 0)
            {
                A.medrez = (A.paz[n/2 - 1] + A.paz[n/2]) / 2.0;
            }
            else
            {
                A.medrez = A.paz[n/2];
            }
            A.medrez = A.medrez * 0.4 + A.egz * 0.6;
        }

        grupe.push_back(A);
        A.paz.clear();

        cout << "Ar toliau vesite mokinius? (y/n): ";
        cin >> ats;
        if (ats == "n")
        {
            break;
        }
        else if (ats == "y")
        {
            cout << "Veskite toliau: ";
        }
        else
        {
            cout << "NETEISINGA IVESTIS, programa veikia toliau" << endl;
        }
    }
}

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
        cout << left << setw(20) << A.vardas
            << setw(20) << A.pavarde
            << right << setw(20) << fixed << setprecision(2) << A.rez
            << setw(20) << A.medrez
            << endl;
    }

    cout << "-------------------------------------------------------------------" << endl;
}

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
        out << left << setw(20) << s.vardas
               << setw(20) << s.pavarde << fixed << setprecision(2)
               << setw(20) << s.rez
               << setw(20) << s.medrez << '\n';
    }
    cout << "Studentu skaicius: " << grupe.size() << endl;
}

void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus)
{
    Studentas A;
    
    string lytis;
    string ats;

    if (ArGeneruotiVardus == true)
    {
        int zmonsk = rand() % 100 + 1;

        for(int iii = 0; iii < zmonsk; iii++)
        {
            int sum = 0;

            lytis = lytgen();
            A.vardas = randomvardas(lytis);
            A.pavarde = randompavarde(lytis);

            int pazsk = rand() % 100 + 1;

            for (int ii = 0; ii < pazsk; ii++)
            {
                int temp = rand() % 10 + 1;
                A.paz.push_back(temp);
                sum += temp;
            }

            A.egz = rand() % 10 + 1;

            if (A.paz.size() > 0)
            {
                A.rez = (sum * 1.0 / A.paz.size()) * 0.4 + A.egz * 0.6;

                sort(A.paz.begin(), A.paz.end());

                int n = A.paz.size();
                if (n % 2 == 0)
                    A.medrez = (A.paz[n/2 - 1] + A.paz[n/2]) / 2.0;
                else
                    A.medrez = A.paz[n/2];
                A.medrez = A.medrez * 0.4 + A.egz * 0.6;
            }

            grupe.push_back(A);
            A.paz.clear();
        }
    }
    else
    {
        while (true)
        {
            int sum = 0;

            cout << "Vardas ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            int pazsk = rand() % 100 + 1;

            for (int i = 0; i < pazsk; i++)
            {
                int temp = rand() % 10 + 1;
                A.paz.push_back(temp);
                sum += temp;
            }

            A.egz = rand() % 10 + 1;

            if (A.paz.size() > 0)
            {
                A.rez = (sum * 1.0 / A.paz.size()) * 0.4 + A.egz * 0.6;

                sort(A.paz.begin(), A.paz.end());

                int n = A.paz.size();
                if (n % 2 == 0)
                    A.medrez = (A.paz[n/2 - 1] + A.paz[n/2]) / 2.0;
                else
                    A.medrez = A.paz[n/2];
                A.medrez = A.medrez * 0.4 + A.egz * 0.6;
            }

            grupe.push_back(A);
            A.paz.clear();

            cout << "Ar toliau vesite zmones? (y/n): ";
            cin >> ats;

            if (ats == "n")
                break;
            else if (ats == "y")
                cout << "Veskite toliau: ";
            else
                cout << "NETEISINGA IVESTIS, programa veikia toliau" << endl;
        }
    }
}

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

        iss >> A.vardas >> A.pavarde;

        int pazymys;

        while (iss >> pazymys)
        {
            A.paz.push_back(pazymys);
        }

        if (!A.paz.empty())
        {
            A.egz = A.paz.back();
            A.paz.pop_back();
        }

        if (!A.paz.empty())
        {
            int sum = 0;
            for (int x : A.paz)
                sum += x;

            sort(A.paz.begin(), A.paz.end());

            if (A.paz.size() % 2 == 0)
                A.medrez = (A.paz[A.paz.size()/2 - 1] + A.paz[A.paz.size()/2]) / 2.0;
            else
                A.medrez = A.paz[A.paz.size()/2];

            A.medrez = A.medrez * 0.4 + A.egz * 0.6;
            A.rez = 0.4 * (sum * 1.0 / A.paz.size()) + 0.6 * A.egz;
        }

        grupe.push_back(A);
    }
}

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
    if (rand() % 2 == 0)
        return "vyr";
    else
        return "mot";
}

bool cmpVardas(const Studentas &a, const Studentas &b)
{
    return a.vardas < b.vardas;
}

bool cmpPavarde(const Studentas &a, const Studentas &b)
{
    return a.pavarde < b.pavarde;
}

bool cmpRez(const Studentas &a, const Studentas &b)
{
    return a.rez < b.rez;
}

bool cmpMedrez(const Studentas &a, const Studentas &b)
{
    return a.medrez < b.medrez;
}

bool cmpEgz(const Studentas &a, const Studentas &b)
{
    return a.egz < b.egz;
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
                << setw(20) << "STUD. PAVARDE" << fixed << setprecision(2) << setw(20) << "STUD PAZYMIAI (PASKUTINIS EGZAMINO) \n";

        for (int genit = 1; genit <= sk; genit++)
        {
            gen << left << setw(20) << "genVardas" + to_string(genit)
                << setw(20) << "genPavarde" + to_string(genit) << fixed << setprecision(2);
            for (int i = 1; i<=16; i++) //15 pazymiu ir 1 egzamino pazymys
            {
                gen << setw(20) << rand() % 10 + 1;
            }
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

        getline(file, line); // praleidziu antraste

        while (getline(file, line))
        {
            istringstream iss(line);

            Studentas A;

            iss >> A.vardas >> A.pavarde;

            int paz;

            while (iss >> paz)
            {
                A.paz.push_back(paz);
            }

            if (A.paz.empty())
                continue;

            A.egz = A.paz.back();
            A.paz.pop_back();

            int sum = 0;

            for (int x : A.paz)
                sum += x;

            A.rez = 0.4 * (sum * 1.0 / A.paz.size()) + 0.6 * A.egz;

            sort(A.paz.begin(), A.paz.end());

            int n = A.paz.size();

            if (n % 2 == 0)
                A.medrez = (A.paz[n/2 - 1] + A.paz[n/2]) / 2.0;
            else
                A.medrez = A.paz[n/2];
            A.medrez = A.medrez * 0.4 + A.egz * 0.6;
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
        {
            skirstyti(grupe, protingi, neprotingi);
        }
        else if (strategija == SkirstymoStrategija::ANTRAS)
        {
            skirstyti2(grupe, neprotingi);
        }
        else if (strategija == SkirstymoStrategija::TRECIAS)
        {
            skirstyti3(grupe, neprotingi);
        }
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
        else if (strategija == SkirstymoStrategija::ANTRAS or strategija == SkirstymoStrategija::TRECIAS)
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
            "vector", // keisti pagal versija
            sk,
            diff_read.count(),
            diff_rikiavimas.count(),
            diff_skirstymas.count()
        );

        sk *= 10;
    }
}

void skirstyti(const vector<Studentas>& grupe, vector<Studentas>& protingi, vector<Studentas>& neprotingi)
{
    for (const auto& s : grupe)
    {
        if (s.rez >= 5.0)
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

void skirstyti2(vector<Studentas>& grupe, vector<Studentas>& neprotingi)
{
    auto it = partition(grupe.begin(), grupe.end(),
        [](const Studentas& s) { return s.rez >= 5.0; });
    neprotingi.assign(it, grupe.end());
    grupe.erase(it, grupe.end()); // protingi paliekami
}

void skirstyti3(vector<Studentas>& grupe, vector<Studentas>& neprotingi)
{
    neprotingi.reserve(grupe.size());
    auto it = remove_if(grupe.begin(), grupe.end(),
        [&](const Studentas& s)
        {
            if (s.rez < 5.0)
            {
                neprotingi.push_back(s);
                return true;
            }
            return false;
        });
    grupe.erase(it, grupe.end());
}







