#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Studentas {
    string vardas = "A", pavarde = "BB";
    vector<int> paz;
    int egz;
    double rez;
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
    Studentas A; // FIX: declare the student object

    for (int ii = 0; ii < 2; ii++)
    {
        int n, sum = 0;

        cout << "Vardas ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        cout << "Kiek pazymiu: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            int temp;
            cout << "Is viso " << n << " pazymiu. Iveskite pazymi numeris " << i + 1 << ": ";
            cin >> temp;

            A.paz.push_back(temp);
            sum += temp;
        }

        cout << "Iveskite egzamino rezultata: ";
        cin >> A.egz;

        A.rez = (sum * 1.0 / n) * 0.4 + A.egz * 0.6;

        grupe.push_back(A);

        A.paz.clear(); // clear for next student
    }
}

void outputas(const vector<Studentas> &grupe)
{
        cout << "-------------------------------------------------------------------" << endl;
            cout << left << setw(15) << "Vardas"
         << left << setw(15) << "Pavarde"
         << right << setw(10) << fixed << setprecision(2) << "Rezultatas"
         << endl;
    for (const auto &A : grupe)
    {
        cout << left << setw(15) << A.vardas
             << left << setw(15) << A.pavarde
             << right << setw(10) << fixed << setprecision(2) << A.rez
             << endl;
    }
}
