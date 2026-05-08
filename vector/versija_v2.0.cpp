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

int main()
{
    srand(time(NULL));

    vector<Studentas> grupe;
    vector<Studentas> protingi;
    vector<Studentas> neprotingi;

    grupe.reserve(10000000);

    string genpas;
    cout << "Norite generuoti 5 failus? y/n " << endl;
    cin >> genpas;
    if (genpas == "y") failgeneravimas();

    cout << "--- Zmogus kurimo testavimas ---" << endl;

    // Zmogus z;

    cout << "--- Rule of Five dalykai ---" << endl;

    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

    cout << setw(20) << "Originalus elementas a: " << a << endl;

    Studentas b(a);          // copy constructor
    cout << setw(20) << "Copy ctor (b konstruojamas su a kopija): " << b << endl;
    a.addPaz(1);
    a.skaiciuoti();
    cout << setw(20) << "a pakeiciamas: " << a << endl;
    cout << setw(20) << "b lieka toks pat: " << b << endl;

    Studentas c;
    c = a;                    // copy assignment
    cout << setw(20) << "Copy assign (c jau egzistuoja ir kopijuoja a): " << c << endl;
    a.addPaz(1);
    c.addPaz(10);
    cout << setw(20) << "a ir c su pazymiu pakeitimais:" << endl;
    a.skaiciuoti();
    c.skaiciuoti();
    cout << setw(20) << "pradinis (a): " << a << endl;
    cout << setw(20) << "kopija (c): " << c << endl;

    Studentas d(move(a));  // move constructor
    cout << setw(20) << "Move ctor (d inicializuojamas move'inant a): " << d << endl;
    cout << setw(20) << "objektas a, is kurio paimta info (a turi buti tuscias): " << endl;
    cout << a << endl;

    Studentas e;
    e = move(b);         // move assignment
    cout << setw(20) << "Move assign (e egzistuoja, b -> e): " << e << endl;
    b.addPaz(1);
    b.skaiciuoti();
    cout << setw(20) << "objektas b pakeiciamas" << endl;
    cout << setw(20) << "objektas b, is kurio paimta info: " << endl;
    cout << b << endl;

    cout << setw(20) << "elementas e lygus elementui e ir yra move'inamas (e -> e): " << endl;
    e = e; // cia tas edge case kur move'ina i ta pati dalyka
    e = move(e);
    cout << e << endl;

    cout << "=== End of Test ===" << endl << endl;


    int pasirinkimas = 4;
    string isvedimotipas, skaitymo_pasirinkimas, skaitymo_failas;
    cout << "Kokios norite ivesties? (1 - ranka arba is failo, 2 - generuoti tik pazymius, " << endl
    << " 3 - generuoti studentu vardus, pavardes ir pazymius, 4 - skaityti sugeneruotus failus; 5 arba kitas simbolis - baigti darba)" << endl;
    cin >> pasirinkimas;

    int rikiavimo_pasirinkimas;
    cout << "Pagal ka rikiuoti?" << endl
    << "1 - vardas" << endl
    << "2 - pavarde" << endl
    << "3 - galutinis (vidurkis)" << endl
    << "4 - galutinis (mediana)" << endl
    << "5 - egzaminas" << endl;
    cin >> rikiavimo_pasirinkimas;


    auto input_start = chrono::high_resolution_clock::now();

    if (pasirinkimas == 1)
    {    
        cout << "Ar skaityti duomenis is failo? (y - is failo / n - ranka)";
        cin >> skaitymo_pasirinkimas;
        if (skaitymo_pasirinkimas == "y")
        {
            string skaitymo_failas;
            cout << "Iveskite failo pavadinima: ";
            cin >> skaitymo_failas;
            failinputas(grupe, skaitymo_failas);
        }
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
    else if (pasirinkimas == 4)
    {
        genirasymas(grupe, protingi, neprotingi, irasymo_failas_geras, irasymo_failas_blogas, rikiavimo_pasirinkimas, SkirstymoStrategija::TRECIAS);
        return 0;
    }
    else
    {
        cout << "darbas baigtas" << endl;
        return 0;
    }

    auto input_end = chrono::high_resolution_clock::now();
    chrono::duration<double> input_diff = input_end - input_start;
    cout << "Duomenu nuskaitymas uztruko: " << input_diff.count() << " s \n";

    cout << "Ar rasyti i faila? (y/n)" << endl;
    cin >> isvedimotipas;

    auto start = std::chrono::high_resolution_clock::now(); // Paleisti

    rikiuoti(grupe, rikiavimo_pasirinkimas);
    //skirstyti(grupe, protingi, neprotingi)
    //skirstyti2(grupe, neprotingi);
    skirstyti3(grupe, neprotingi);

    if (isvedimotipas == "y")
    {
        cout << "pradedu rasyt" << endl;
        failoutputas(protingi, "kursiokai_geri.txt");
        failoutputas(grupe, "kursiokai_geri_grupe.txt");
        failoutputas(neprotingi, "kursiokai_blogi.txt");
        cout << "Baigiu rasyt" << endl;
    }
    else
    {
        outputas(grupe);
    }

    // is pavyzdzio
    auto end = chrono::high_resolution_clock::now(); // Stabdyti
    chrono::duration<double> diff = end-start; // Skirtumas (s)
    cout << "Programos rikiavimas ir isvedimas uztruko: "<< diff.count() << " s\n";

    cout << "program finished." << endl;
    return 0;
}