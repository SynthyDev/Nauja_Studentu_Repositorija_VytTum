#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct Studentas {
    string vardas = "A", pavarde = "BB";
    vector<int> paz;
    int egz;
    double rez;
    double medrez;
};

void inputas(vector<Studentas> &grupe);
void outputas(const vector<Studentas> &grupe);

int main()
{
    vector<Studentas> grupe;
    inputas(grupe);
    outputas(grupe);
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

        A.rez = (sum * 1.0 / A.paz.size()) * 0.4 + A.egz * 0.6;

        sort(A.paz.begin(), A.paz.end());

        if (A.paz.size() % 2 == 0)
        {
            A.medrez = (A.paz[floor(A.paz.size()*1.0/2.0 - 1)] + A.paz[ceil(A.paz.size()*1.0/2.0)]) / 2.0;
        }
        else
        {
            A.medrez = A.paz[floor(A.paz.size()/2)];
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
        cout << left << setw(15) << "Vardas"
         << left << setw(15) << "Pavarde"
         << right << setw(10) << fixed << setprecision(2) << "Rezultatas (Vid.)  /  Rezultatas (Med.)"
         << endl;
        cout << "-------------------------------------------------------------------" << endl;
    for (const auto &A : grupe)
    {
        cout << left << setw(15) << A.vardas
             << left << setw(15) << A.pavarde
             << right << setw(10) << fixed << setprecision(2) << A.rez
             << right << setw(20) << A.medrez
             << endl;
    }
    cout << "-------------------------------------------------------------------" << endl;
}
