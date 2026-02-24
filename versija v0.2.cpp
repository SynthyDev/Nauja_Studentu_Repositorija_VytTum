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

using namespace std;

const vector<string> mvardai = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const vector<string> fvardai = {"Eglė", "Viktorija", "Vakarė", "Inga", "Ema", "Marija", "Janina"};
const vector<string> pavardes = {"Mačerausk", "Jankausk", "Kazlausk", "Švilpausk", "Drugėliausk", "Briedausk"};
const vector<string> mgalunes = {"as", "aitis"};
const vector<string> fgalunes = {"ienė", "aitė", "ytė"};

struct Studentas {
    string vardas = "A", pavarde = "BB";
    vector<int> paz;
    int egz;
    double rez;
    double medrez;
};

const string skaitymo_failas = "studentai10000.txt";
const string irasymo_failas = "kursiokai.txt";

void inputas(vector<Studentas> &grupe);
void failinputas(vector<Studentas> &grupe, string reading);
void randominputas(vector<Studentas> &grupe, bool ArGeneruotiVardus);
void outputas(const vector<Studentas> &grupe);
void failoutputas(const vector<Studentas> &grupe);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);

int main()
{
    srand(time(NULL));
    
    ofstream irasymas(irasymo_failas);

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

    if (isvedimotipas == "y")
    {
        failoutputas(grupe);
    }
    else
    {
        outputas(grupe);
    }

    irasymas.close();

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

void failoutputas(const vector<Studentas> &grupe)
{
    cout << "this is a test" << endl;
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

void failinputas(vector<Studentas> &grupe, string reading) // check vector shenanigans, probably need to store in separate vector
{
    ifstream file(reading);

    if (!file) {
        cout << "Nepavyko atidaryti failo\n";
        return;
    }

    string line;

    while (getline(file, line))
    {
        istringstream iss(line);

        Studentas temp;

        iss >> temp.vardas >> temp.pavarde;

        int pazymys;

        while (iss >> pazymys)
        {
            temp.paz.push_back(pazymys);
        }

        if (!temp.paz.empty())
        {
            temp.egz = temp.paz.back();
            temp.paz.pop_back();
        }

        grupe.push_back(temp);
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
