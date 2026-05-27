Kaip naudoti Makefile?
1. Atidarykite aplanką, kurio programą norite paleist (pvz. vector)
2. Būtina turėti MinGW64 arba kitą įrankį, kuris palaiko "make" funkciją: https://gnuwin32.sourceforge.net/packages/make.htm
4. Atidarykite terminalą pasirinktame aplanke.
5. terminale įrašykite šią užklausą: make
6. Paspauskite du kartus pele ant "programa.exe" failo ARBA terminale parašykite programa.exe (priklauso nuo OS).
7. Turėtų iššokti langas, kuriame veiks pasirinkta programa. Joje galite įrašyti parametrus ir pasirinkti programos funkcijas.
---
DOKUMENTACIJA:

Dokumentacija padaryta naudojant Doxygen (latex ir html generavimui) bei Overleaf (PDF failo generavimui)

<img width="1107" height="227" alt="image" src="https://github.com/user-attachments/assets/e22784b5-0e5a-447a-9a1c-2032deaa4dd0" />

Dokumentacijos PDF failas "Documentation" aplanke.

---
VERSIJA V3.0
---
Pridėta Vector implementacija vietoj std::vector (faile Vector2.h)

Greičių testavimas ir lyginimas std::vector prieš Vector pildant tuščius vektorius įvairiais dydžiais:

<img width="948" height="673" alt="image" src="https://github.com/user-attachments/assets/58810fd8-2644-4564-b860-2aa1c0f72bf0" />
<img width="451" height="194" alt="image" src="https://github.com/user-attachments/assets/5636d41a-020a-4ced-8175-412c115dac1e" />

Taigi mano versija lėtesnė, bet nedaug. Iš esmės su mažais skaičiais laikas panašus. Aišku, kad mano implementacija nėra pilna ar taip optimizuota, kaip gali būti. Vis dėlto rezultatas tenkinantis, pakankamai panašus, netgi su dideliais skaičiais.

Programos veikimo (failų nuskaitymo) patikrinimas:
<img width="532" height="390" alt="image" src="https://github.com/user-attachments/assets/b7d99e2d-0ef9-4c55-8d26-23b3cd5d8515" />

---
VERSIJA V2.0
---
TESTAVIMAS:

Viskas dabar testuojama su Unit Testais, naudojant catch2 framework'ą.

Unit testų pavyzdžiai Klasėms ir Rule of 5 dalykams:

<img width="1464" height="152" alt="image" src="https://github.com/user-attachments/assets/396d341b-c36c-4bef-84af-b4c2e2a357c0" />

<img width="719" height="934" alt="image" src="https://github.com/user-attachments/assets/0d69bca4-b311-4f51-9112-e11e84799b1e" />

---
VERSIJOS V1.2 DALYKAI
---
<img width="1298" height="257" alt="image" src="https://github.com/user-attachments/assets/c40a0247-d535-4a96-b6e0-c8a7c17f469a" />
(penkiu taisykliu testavimas)

Kaip veikia 5 taisyklės:

Destruktorius

Kopijavimo konstruktorius

Kopijavimo priskyrimo operatorius

Perkėlimo konstruktorius

Perkėlimo priskyrimo operatorius

(visi buvo pridėti prie klasės funkcionalumo)

Operatorių persidengimas:

operator<< leidžia rašyti išvedimą kaip <<

pvz

cout << Studentas;

(rodomas vardas, pavardė, galutinis pažymių vidurkis su ir be medianos)

operator>> leidžia rašyti įvedimą kaip >>

pvz

cin >> Studentas;

Nuskaito:

vardą ir pavardę

visus pažymius iki eilutės pabaigos

Paskutinį pažymį traktuoja kaip egzaminą

Perskaičiuoja vidurkį ir medianą
