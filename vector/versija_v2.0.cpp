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

    vector<Studentas> grupe;        //! Main student group
    vector<Studentas> protingi;     //! Students with >=5 result
    vector<Studentas> neprotingi;   //! Students with <5 result

    grupe.reserve(10000000);        //! Pre-reserve for performance

    string genpas;
    cout << "Norite generuoti 5 failus? y/n " << endl;
    cin >> genpas;
    if (genpas == "y") failgeneravimas(); //! Generate test files

    cout << "--- Zmogus kurimo testavimas ---" << endl;

    cout << "--- Rule of Five dalykai ---" << endl;

    Studentas a; //! Test object for Rule of Five
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

    cout << setw(20) << "Original: " << a << endl;

    Studentas b = a;          //! Copy constructor
    cout << setw(20) << "Copy ctor: " << b << endl;

    Studentas c;
    c = a;                    //! Copy assignment
    cout << setw(20) << "Copy assign: " << c << endl;

    Studentas d = move(a);    //! Move constructor
    cout << setw(20) << "Move ctor: " << d << endl;

    Studentas e;
    e = move(b);              //! Move assignment
    cout << setw(20) << "Move assign: " << e << endl;

    cout << "=== End of Test ===" << endl << endl;


    int pasirinkimas = 4;
    string isvedimotipas, skaitymo_pasirinkimas, skaitymo_failas;

    cout << "Kokios norite ivesties? ..." << endl;
    cin >> pasirinkimas;

    int rikiavimo_pasirinkimas;
    cout << "Pagal ka rikiuoti?" << endl;
    cin >> rikiavimo_pasirinkimas;

    auto input_start = chrono::high_resolution_clock::now(); //! Start timing input

    if (pasirinkimas == 1)
    {
        //! Manual or file input
        cout << "Ar skaityti duomenis is failo? (y/n)";
        cin >> skaitymo_pasirinkimas;
        if (skaitymo_pasirinkimas == "y")
        {
            cout << "Iveskite failo pavadinima: ";
            cin >> skaitymo_failas;
            failinputas(grupe, skaitymo_failas);
        }
        else inputas(grupe);
    }
    else if (pasirinkimas == 2)
    {
        randominputas(grupe, false); //! Random grades only
    }
    else if (pasirinkimas == 3)
    {
        randominputas(grupe, true); //! Random names + grades
    }
    else if (pasirinkimas == 4)
    {
        //! Read generated files and process them
        genirasymas(grupe, protingi, neprotingi,
                    irasymo_failas_geras, irasymo_failas_blogas,
                    rikiavimo_pasirinkimas, SkirstymoStrategija::TRECIAS);
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

    auto start = chrono::high_resolution_clock::now(); //! Start sorting/splitting timer

    rikiuoti(grupe, rikiavimo_pasirinkimas); //! Sort students

    skirstyti3(grupe, neprotingi); //! Split using remove_if

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
        outputas(grupe); //! Print to console
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Programos rikiavimas ir isvedimas uztruko: "<< diff.count() << " s\n";

    cout << "program finished." << endl;
    return 0;
}
