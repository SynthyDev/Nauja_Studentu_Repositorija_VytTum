#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "studentai.h"
#include <type_traits>

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

TEST_CASE("Rule of 5 nr1: copy konstruktorius") {
    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

}

TEST_CASE("Rule of 5 nr2: copy assignment") {
    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

}

TEST_CASE("Rule of 5 nr3: move konstruktorius") {
    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

}

TEST_CASE("Rule of 5 nr4: copy assignment") {
    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

}

TEST_CASE("Rule of 5 nr5: a -> a") {
    Studentas a;
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPaz(10);
    a.addPaz(9);
    a.setEgz(8);
    a.skaiciuoti();

}