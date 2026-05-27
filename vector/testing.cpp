#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "studentai.h"
#include <type_traits>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Vector2.h"

TEST_CASE("Studentu klases testas") {
    Studentas A;

    A.setVardas("Zygimantas");
    A.setPavarde("Rauba");
    A.addPaz(10);
    A.setEgz(6);

    A.skaiciuoti();

    REQUIRE(A.getVardas() == "Zygimantas");
    REQUIRE(A.getPavarde() == "Rauba");
    REQUIRE(A.getPaz() == my::Vector<int>{10});
    REQUIRE(A.getEgz() == 6);
    REQUIRE(A.getRez() == 7.60);
    REQUIRE(A.getMedrez() == 7.60);
}

TEST_CASE("Zmogus yra abstract") {
    REQUIRE(std::is_abstract_v<Zmogus>);
}

TEST_CASE("Ar studentas yra abstract?") {
    REQUIRE_FALSE(std::is_abstract_v<Studentas>);
}

Studentas makeStudent() {
    Studentas s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.addPaz(10);
    s.addPaz(9);
    s.setEgz(8);
    s.skaiciuoti();
    return s;
}

TEST_CASE("Studentas copy konstruktorius") {
    Studentas a = makeStudent();
    Studentas b(a);

    REQUIRE(b.getVardas() == "Jonas");
    REQUIRE(b.getPavarde() == "Jonaitis");
    REQUIRE(b.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(b.getEgz() == 8);
    REQUIRE(b.getRez() == 8.60);
    REQUIRE(b.getMedrez() == 8.60);
}

TEST_CASE("Studentas copy assignment") {
    Studentas a = makeStudent();
    Studentas b;
    b = a;

    REQUIRE(b.getVardas() == "Jonas");
    REQUIRE(b.getPavarde() == "Jonaitis");
    REQUIRE(b.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(b.getEgz() == 8);
    REQUIRE(b.getRez() == 8.60);
    REQUIRE(b.getMedrez() == 8.60);

    b.addPaz(5);
    a.addPaz(2);
    a.skaiciuoti();
    b.skaiciuoti();

    REQUIRE(b.getRez() == 8.00);
    REQUIRE(a.getRez() == 7.60);
}

TEST_CASE("Studentas move konostruktorius") {
    Studentas a = makeStudent();
    Studentas b(move(a));

    REQUIRE(b.getVardas() == "Jonas");
    REQUIRE(b.getPavarde() == "Jonaitis");
    REQUIRE(b.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(b.getEgz() == 8);
    REQUIRE(b.getRez() == 8.60);
    REQUIRE(b.getMedrez() == 8.60);

    b.addPaz(5);
    a.addPaz(2);
    a.skaiciuoti();
    b.skaiciuoti();

    REQUIRE(b.getRez() == 8.00);
    REQUIRE(a.getRez() == 0.80); // del to, kad a tampa tuscias ir vienintelis pazymys yra 2
}

TEST_CASE("Studentas move assignment") {
    Studentas a = makeStudent();
    Studentas b;
    b = move(a);


    REQUIRE(b.getVardas() == "Jonas");
    REQUIRE(b.getPavarde() == "Jonaitis");
    REQUIRE(b.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(b.getEgz() == 8);
    REQUIRE(b.getRez() == 8.60);
    REQUIRE(b.getMedrez() == 8.60);

    b.addPaz(5);
    a.addPaz(2);
    a.skaiciuoti();
    b.skaiciuoti();

    REQUIRE(b.getRez() == 8.00);
    REQUIRE(a.getRez() == 0.80); // del to, kad a tampa tuscias ir vienintelis pazymys yra 2
    REQUIRE(a.getVardas().empty());
    REQUIRE(a.getPavarde().empty());
    REQUIRE(a.getEgz() == 0);
}

TEST_CASE("Studentas move a -> a") {
    Studentas a = makeStudent();
    a = move(a);

    REQUIRE(a.getVardas() == "Jonas");
    REQUIRE(a.getPavarde() == "Jonaitis");
    REQUIRE(a.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(a.getEgz() == 8);
    REQUIRE(a.getRez() == 8.60);
    REQUIRE(a.getMedrez() == 8.60);

    REQUIRE(a.getRez() == 8.60); // del to, kad a tampa tuscias ir vienintelis pazymys yra 2
}

TEST_CASE("Studentas output operator >>") {
    Studentas s = makeStudent();

    std::ostringstream out;
    out << s;

    std::string result = out.str();

    REQUIRE(result.find("Jonas") != std::string::npos);
    REQUIRE(result.find("Jonaitis") != std::string::npos);
    REQUIRE(result.find("8.60") != std::string::npos);
}

TEST_CASE("Studentas input operator >>") {
    std::istringstream input("Jonas Jonaitis 10 9 8");

    Studentas s;
    input >> s;

    REQUIRE(s.getVardas() == "Jonas");
    REQUIRE(s.getPavarde() == "Jonaitis");
    REQUIRE(s.getPaz() == my::Vector<int>{10, 9});
    REQUIRE(s.getEgz() == 8);
}

TEST_CASE("Vector default constructor") {
    Vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("Vector initializer_list constructor") {
    Vector<int> v{1, 2, 3};
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Vector fill constructor") {
    Vector<int> v(5, 7);
    REQUIRE(v.size() == 5);
    for (int x : v) REQUIRE(x == 7);
}

TEST_CASE("Vector copy constructor") {
    Vector<int> a{1, 2, 3};
    Vector<int> b(a);

    REQUIRE(b.size() == 3);
    REQUIRE(b == a);

    b[0] = 99;
    REQUIRE(a[0] == 1); // deep copy
}

TEST_CASE("Vector copy assignment") {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    b = a;

    REQUIRE(b.size() == 3);
    REQUIRE(b == a);

    b[1] = 77;
    REQUIRE(a[1] == 2);
}

TEST_CASE("Vector move constructor") {
    Vector<int> a{1, 2, 3};
    Vector<int> b(std::move(a));

    REQUIRE(b.size() == 3);
    REQUIRE(b[0] == 1);
    REQUIRE(a.size() == 0);
    REQUIRE(a.capacity() == 0);
}

TEST_CASE("Vector move assignment") {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    b = std::move(a);

    REQUIRE(b.size() == 3);
    REQUIRE(b[2] == 3);
    REQUIRE(a.size() == 0);
    REQUIRE(a.capacity() == 0);
}

TEST_CASE("Vector push_back and pop_back") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    REQUIRE(v.size() == 3);
    REQUIRE(v.back() == 30);

    v.pop_back();
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 20);
}

TEST_CASE("Vector reserve increases capacity but not size") {
    Vector<int> v;
    v.reserve(50);
    REQUIRE(v.capacity() >= 50);
    REQUIRE(v.size() == 0);
}

TEST_CASE("Vector resize larger") {
    Vector<int> v{1, 2, 3};
    v.resize(5, 9);

    REQUIRE(v.size() == 5);
    REQUIRE(v[3] == 9);
    REQUIRE(v[4] == 9);
}

TEST_CASE("Vector resize smaller") {
    Vector<int> v{1, 2, 3, 4, 5};
    v.resize(2);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
}

TEST_CASE("Vector at() throws on out of range") {
    Vector<int> v{1, 2, 3};
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}

TEST_CASE("Vector front() and back()") {
    Vector<int> v{10, 20, 30};
    REQUIRE(v.front() == 10);
    REQUIRE(v.back() == 30);
}

TEST_CASE("Vector iterators work") {
    Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
        sum += *it;

    REQUIRE(sum == 6);
}

TEST_CASE("Vector reverse iterators") {
    Vector<int> v{1, 2, 3};
    REQUIRE(*v.rbegin() == 3);
    REQUIRE(*(v.rbegin() + 1) == 2);
}

TEST_CASE("Vector insert at middle") {
    Vector<int> v{1, 2, 4};
    v.insert(v.begin() + 2, 3);

    REQUIRE(v.size() == 4);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Vector erase single element") {
    Vector<int> v{1, 2, 3, 4};
    v.erase(v.begin() + 1);

    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 3);
}

TEST_CASE("Vector erase range") {
    Vector<int> v{1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 4);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 5);
}

TEST_CASE("Vector comparison operators") {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    Vector<int> c{1, 2, 4};

    REQUIRE(a == b);
    REQUIRE(a != c);
    REQUIRE(a < c);
    REQUIRE(c > b);
}

TEST_CASE("Vector swap") {
    Vector<int> a{1, 2};
    Vector<int> b{9, 8, 7};

    a.swap(b);

    REQUIRE(a.size() == 3);
    REQUIRE(b.size() == 2);
    REQUIRE(a[0] == 9);
    REQUIRE(b[1] == 2);
}

TEST_CASE("Vector clear") {
    Vector<int> v{1, 2, 3};
    v.clear();

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 3); // capacity stays
}
