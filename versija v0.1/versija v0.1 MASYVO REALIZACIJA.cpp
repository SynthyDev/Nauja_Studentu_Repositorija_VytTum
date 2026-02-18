#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_PAZ = 100;
const int MAX_STUD = 100;

const string mvardai[] = {"Vytenis", "Tomas", "Jonas", "Matas", "Simas", "Mantas", "Arnas"};
const string fvardai[] = {"Eglė", "Viktorija", "Vakarė", "Inga", "Ema", "Marija", "Janina"};
const string pavardes[] = {"Mačerausk", "Jankausk", "Kazlausk", "Švilpausk", "Drugėliausk", "Briedausk"};
const string mgalunes[] = {"as", "aitis"};
const string fgalunes[] = {"ienė", "aitė", "ytė"};

struct Studentas {
    string vardas = "A", pavarde = "BB";
    int paz[MAX_PAZ];
    int pazkiek = 0;
    int egz;
    double rez;
    double medrez;
};

void inputas(Studentas grupe[], int &studkiek);
void randominputas(Studentas grupe[], int &studkiek, bool ArGeneruotiVardus);
void outputas(const Studentas grupe[], int studkiek);
string lytgen();
string randomvardas(string lytis);
string randompavarde(string lytis);

int main()
{
    srand(time(NULL));
    
    Studentas grupe[MAX_STUD];
    int studkiek = 0;

    int pasirinkimas = 4;
    cout << "Kokios norite ivesties? (1 - ranka, 2 - generuoti tik pazymius, " << endl
         << " 3 - generuoti studentu vardus, pavardes ir pazymius, 4 arba kitas simbolis - baigti darba)" << endl;
    cin >> pasirinkimas;

    if (pasirinkimas == 1)
    {
        inputas(grupe, studkiek);
        outputas(grupe, studkiek);
    }
    else if (pasirinkimas == 2)
    {
        randominputas(grupe, studkiek, false);
        outputas(grupe, studkiek);
    }
    else if (pasirinkimas == 3)
    {
        randominputas(grupe, studkiek, true);
        outputas(grupe, studkiek);
    }
    else
    {
        cout << "darbas baigtas" << endl;
    }

    return 0;
}

void inputas(Studentas grupe[], int &studkiek)
{
    Studentas A;

    while (true)
    {
        int sum = 0;

        cout << "Vardas ir pavarde: ";
        cin >> A.vardas >> A.pavarde;

        A.pazkiek = 0;
        string ats;
        int i = 0;

        while (true)
        {
            int temp;
            cout << "Iveskite pazymi numeris " << i + 1 << ": ";
            cin >> temp;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Bloga ivestis. Bandykite dar karta.\n";
                continue;
            }

            if (A.pazkiek < MAX_PAZ)
            {
                A.paz[A.pazkiek++] = temp;
            }

            sum += temp;

            cout << "Ar baigete vesti pazymius? (y/n): ";
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

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Bloga ivestis. Bandykite dar karta.\n";
            continue;
        }

        if (A.pazkiek > 0)
        {
            A.rez = (sum * 1.0 / A.pazkiek) * 0.4 + A.egz * 0.6;

            sort(A.paz, A.paz + A.pazkiek);

            if (A.pazkiek % 2 == 0)
                A.medrez = (A.paz[A.pazkiek/2 - 1] + A.paz[A.pazkiek/2]) / 2.0;
            else
                A.medrez = A.paz[A.pazkiek/2];
        }

        if (studkiek < MAX_STUD)
            grupe[studkiek++] = A;

        cout << "Ar baigete vesti mokinius? (y/n): ";
        cin >> ats;
        if (ats == "y")
            break;
        else if (ats == "n")
            cout << "Veskite toliau: ";
        else
            cout << "NETEISINGA IVESTIS, programa veikia toliau" << endl;
    }
}

void outputas(const Studentas grupe[], int studkiek)
{
    cout << "-------------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(20) << "Rezultatas (Vid.) /"
         << setw(20) << " Rezultatas (Med.)"
         << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < studkiek; i++)
    {
        const Studentas &A = grupe[i];
        cout << left << setw(20) << A.vardas
             << setw(20) << A.pavarde
             << right << setw(20) << fixed << setprecision(2) << A.rez
             << setw(20) << A.medrez
             << endl;
    }

    cout << "-------------------------------------------------------------------" << endl;
}

void randominputas(Studentas grupe[], int &studkiek, bool ArGeneruotiVardus)
{
    Studentas A;
    string lytis, ats;

    if (ArGeneruotiVardus)
    {
        int zmonsk = rand() % MAX_STUD + 1;
        for (int iii = 0; iii < zmonsk && studkiek < MAX_STUD; iii++)
        {
            int sum = 0;

            lytis = lytgen();
            A.vardas = randomvardas(lytis);
            A.pavarde = randompavarde(lytis);

            A.pazkiek = rand() % MAX_PAZ + 1;
            for (int ii = 0; ii < A.pazkiek; ii++)
            {
                int temp = rand() % 10 + 1;
                A.paz[ii] = temp;
                sum += temp;
            }

            A.egz = rand() % 10 + 1;

            if (A.pazkiek > 0)
            {
                A.rez = (sum * 1.0 / A.pazkiek) * 0.4 + A.egz * 0.6;
                sort(A.paz, A.paz + A.pazkiek);

                if (A.pazkiek % 2 == 0)
                    A.medrez = (A.paz[A.pazkiek/2 - 1] + A.paz[A.pazkiek/2]) / 2.0;
                else
                    A.medrez = A.paz[A.pazkiek/2];
            }

            grupe[studkiek++] = A;
        }
    }
    else
    {
        while (true)
        {
            int sum = 0;

            cout << "Vardas ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            A.pazkiek = rand() % MAX_PAZ + 1;
            for (int i = 0; i < A.pazkiek; i++)
            {
                int temp = rand() % 10 + 1;
                A.paz[i] = temp;
                sum += temp;
            }

            A.egz = rand() % 10 + 1;

            if (A.pazkiek > 0)
            {
                A.rez = (sum * 1.0 / A.pazkiek) * 0.4 + A.egz * 0.6;
                sort(A.paz, A.paz + A.pazkiek);

                if (A.pazkiek % 2 == 0)
                    A.medrez = (A.paz[A.pazkiek/2 - 1] + A.paz[A.pazkiek/2]) / 2.0;
                else
                    A.medrez = A.paz[A.pazkiek/2];
            }

            if (studkiek < MAX_STUD)
                grupe[studkiek++] = A;

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

string randomvardas(string lytis)
{
    if (lytis == "mot")
        return fvardai[rand() % (sizeof(fvardai)/sizeof(fvardai[0]))];
    else
        return mvardai[rand() % (sizeof(mvardai)/sizeof(mvardai[0]))];
}

string randompavarde(string lytis)
{
    int index = rand() % (sizeof(pavardes)/sizeof(pavardes[0]));
    string galune;

    if (lytis == "mot")
        galune = fgalunes[rand() % (sizeof(fgalunes)/sizeof(fgalunes[0]))];
    else
        galune = mgalunes[rand() % (sizeof(mgalunes)/sizeof(mgalunes[0]))];

    return pavardes[index] + galune;
}

string lytgen()
{
    return (rand() % 2 == 0) ? "vyr" : "mot";
}
