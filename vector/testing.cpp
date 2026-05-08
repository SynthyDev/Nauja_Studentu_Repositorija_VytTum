#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "studentai.h"

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
