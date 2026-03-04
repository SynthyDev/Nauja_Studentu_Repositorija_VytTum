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
