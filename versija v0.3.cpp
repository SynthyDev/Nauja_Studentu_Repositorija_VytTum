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

using namespace std;

// 5 PALEIDIMU VIDUTINIS LAIKAS (rikiavimas + output):
// 1 000 000 eiluciu:
// undetermined ~ 90 s iš viso, rodo ~3.5 s
// 100 000 eiluciu:
// (0.36 + 0.36 + 0.35 + 0.36 + 0.35) / 5 = 0.356 s
// 10 000 eiluciu:
// (0.032 + 0.031 + 0.034 + 0.033 + 0.031) / 5 = 0.032


int main()
{
    srand(time(NULL));

    vector<Studentas> grupe;

    int pasirinkimas = 4;
    string isvedimotipas, skaitymo_pasirinkimas;
    cout << "Kokios norite ivesties? (1 - ranka arba iš failo, 2 - generuoti tik pažymius, " << endl
    << " 3 - generuoti studentų vardus, pavardės ir pažymius, 4 arba kitas simbolis - baigti darbą)" << endl;
    cin >> pasirinkimas;

    if (pasirinkimas == 1)
    {    
        cout << "Ar skaityti duomenis iš failo? (y - iš failo / n - ranka)";
        cin >> skaitymo_pasirinkimas;
        if (skaitymo_pasirinkimas == "y") failinputas(grupe, skaitymo_failas);
        else inputas(grupe);
    }
    else if (pasirinkimas == 2)
    {
        randominputas(grupe, false);
    }
    else if (pasirinkimas == 3)
    {
        randominputas(grupe, true);
    }
    else
    {
        cout << "darbas baigtas" << endl;
        return 0;
    }

    cout << "Ar rašyti į failą? (y/n)" << endl;
    cin >> isvedimotipas;

    int rikiavimo_pasirinkimas;
    cout << "Pagal ka rikiuoti?" << endl
    << "1 - vardas" << endl
    << "2 - pavarde" << endl
    << "3 - galutinis (vidurkis)" << endl
    << "4 - galutinis (mediana)" << endl
    << "5 - egzaminas" << endl;
    cin >> rikiavimo_pasirinkimas;

    auto start = std::chrono::high_resolution_clock::now(); // Paleisti

    rikiuoti(grupe, rikiavimo_pasirinkimas);

    if (isvedimotipas == "y")
    {
        cout << "pradedu rasyt" << endl;
        failoutputas(grupe, irasymo_failas);
        cout << "Baigiu rasyt" << endl;
    }
    else
    {
        outputas(grupe);
    }

    // is pavyzdzio
    auto end = chrono::high_resolution_clock::now(); // Stabdyti
    chrono::duration<double> diff = end-start; // Skirtumas (s)
    cout << "Programos rikiavimas ir išvedimas užtruko: "<< diff.count() << " s\n";

    cout << "program finished." << endl;
    return 0;
}

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
            cin >> temp;

            if (cin.fail()) // patikra
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Bloga ivestis. Bandykite dar karta.\n";
                continue;
            }

            A.paz.push_back(temp);
            sum += temp;

            cout << "Ar baigete vesti pažymius? (y/n): ";
            cin >> ats;
            if (ats == "y")
            {
                break;
            }
            else if (ats == "n")
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
        cin >> A.egz;

        if (cin.fail()) // patikra
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Bloga ivestis. Bandykite dar karta.\n";
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
        }

        grupe.push_back(A);
        A.paz.clear();

        cout << "Ar baigete vesti mokinius? (y/n): ";
        cin >> ats;
        if (ats == "y")
        {
            break;
        }
        else if (ats == "n")
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
            }

            grupe.push_back(A);
            A.paz.clear();

            cout << "Ar baigete vesti zmones? (y/n): ";
            cin >> ats;

            if (ats == "y")
                break;
            else if (ats == "n")
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

