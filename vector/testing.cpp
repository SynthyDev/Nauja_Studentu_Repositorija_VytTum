#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "studentai.h"
#include <type_traits>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

TEST_CASE("Studentu klases testas") {
    Studentas A;

    A.setVardas("Zygimantas");
    A.setPavarde("Rauba");
    A.addPaz(10);
    A.setEgz(6);

    A.skaiciuoti();

    REQUIRE(A.getVardas() == "Zygimantas");
    REQUIRE(A.getPavarde() == "Rauba");
    REQUIRE(A.getPaz() == std::vector<int>{10});
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
    REQUIRE(b.getPaz() == std::vector<int>{10, 9});
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
    REQUIRE(b.getPaz() == std::vector<int>{10, 9});
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
    Studentas b;
    b = a;

    REQUIRE(b.getVardas() == "Jonas");
    REQUIRE(b.getPavarde() == "Jonaitis");
    REQUIRE(b.getPaz() == std::vector<int>{10, 9});
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




// output and input operators !!!
// 