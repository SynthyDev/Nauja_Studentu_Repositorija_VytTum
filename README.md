Kaip naudoti Makefile?
1. Atidarykite aplanką, kurio programą norite paleist (pvz. vector)
2. Būtina turėti MinGW64 arba kitą įrankį, kuris palaiko "make" funkciją: https://gnuwin32.sourceforge.net/packages/make.htm
4. Atidarykite terminalą pasirinktame aplanke.
5. terminale įrašykite šią užklausą: make
6. Paspauskite du kartus pele ant "programa.exe" failo ARBA terminale parašykite programa.exe (priklauso nuo OS).
7. Turėtų iššokti langas, kuriame veiks pasirinkta programa. Joje galite įrašyti parametrus ir pasirinkti programos funkcijas.

---
VERSIJA V2.0
---
TESTAVIMAS:

Viskas dabar testuojama su Unit Testais, naudojant catch2 framework'ą.

Unit testų pavyzdžiai Klasėms ir Rule of 5 dalykams:

<img width="1464" height="152" alt="image" src="https://github.com/user-attachments/assets/396d341b-c36c-4bef-84af-b4c2e2a357c0" />

<img width="719" height="934" alt="image" src="https://github.com/user-attachments/assets/0d69bca4-b311-4f51-9112-e11e84799b1e" />


---
DOKUMENTACIJA:

Dokumentacija padaryta naudojant Doxygen (latex ir html generavimui) bei Overleaf (PDF failo generavimui)

<img width="1107" height="227" alt="image" src="https://github.com/user-attachments/assets/e22784b5-0e5a-447a-9a1c-2032deaa4dd0" />

Dokumentacijos PDF failas "Documentation" aplanke.

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

---
Versija v1.1
Viskas pakeista į Class tipą.
funkcionalumas tas pats

EFEKTYVUMAS -O1:

<img width="1260" height="497" alt="image" src="https://github.com/user-attachments/assets/d12a70a7-ab53-409f-ad2c-3718acda370a" />
<img width="1067" height="49" alt="image" src="https://github.com/user-attachments/assets/b8168ffd-73b9-4b93-a151-f91c5a0836ec" />

EFEKTYVUMAS -O2:

<img width="1360" height="539" alt="image" src="https://github.com/user-attachments/assets/990eb948-ff5e-4110-829a-e9645bd26d8a" />
<img width="1073" height="54" alt="image" src="https://github.com/user-attachments/assets/357011fd-3872-483e-91af-37e251c278e8" />

EFEKTYVUMAS -O3:

<img width="1358" height="572" alt="image" src="https://github.com/user-attachments/assets/886294ab-ed9d-40ab-b9c9-9c3602d6c5fb" />
<img width="1066" height="55" alt="image" src="https://github.com/user-attachments/assets/172d611c-c865-42a1-a58c-09641d2f941e" />

---
***VERSIJA V1.0 - PRADINIS RELEASE***
---
Kompiuterio parametrai testavimo metu:
RAM: 16GB RAM DDR5-4800
SSD: 512 GB SSD PCIe
CPU: 12th Gen Intel(R) Core(TM) i5-12500H (16 CPUs), ~2.5GHz
OS: Windows 11 Home 64
---

Matuoti laikai (1 strategija, nes subrelease, po 5 paleidimus):
Deque:
<img width="1102" height="806" alt="image" src="https://github.com/user-attachments/assets/1aa5c52a-4217-4100-81e8-0b38e0c2c486" />

List:
<img width="871" height="677" alt="image" src="https://github.com/user-attachments/assets/6ddeb9bb-06f0-4506-a98a-bdd00162eeff" />

Vector:
<img width="1178" height="821" alt="image" src="https://github.com/user-attachments/assets/bfc86d25-ba96-4f30-b756-f849a714b86e" />

---
VERSIJA V1.0 - GALUTINIS RELEASE
---
2 STRATEGIJA
---

Vector:

<img width="1112" height="899" alt="image" src="https://github.com/user-attachments/assets/0bf33ccf-926c-4c42-9ad9-278954d9b80f" />


Deque:

<img width="1195" height="898" alt="image" src="https://github.com/user-attachments/assets/46d13bd6-df8c-4a82-9320-f21d931107a1" />


List:

<img width="1186" height="781" alt="image" src="https://github.com/user-attachments/assets/265789c3-b10b-4edf-a391-ec45e12b0257" />


Pastebėjimai:
(lyginant su pirmąja strategija)
Su antrąja strategija, vector realizacijos stundentų skirstymo laikas sumažėjo beveik septynis kartus, o list realizacijoje - apie 4.5 kartus.
Kaip ne keista, deque realizacijoje skirstymo laikas reikšmingai nepakito, manau, dėl to, kad su deque objektų perkėlimas ir taip užima daug laiko,
taigi antroji strategija nelabai ką optimizuoja (palyginus su tuo, ką deque ir taip daro).

---
3 STRATEGIJA
---

Vector:

<img width="1138" height="820" alt="image" src="https://github.com/user-attachments/assets/105b151e-58ca-49fd-af4b-9701c342a8aa" />


Deque:

<img width="984" height="793" alt="image" src="https://github.com/user-attachments/assets/3696926a-9660-44e4-8ef3-8d74ec2fa696" />


List:

Listo 2 ir 3 strategijos tapačios (nežinau kaip kitaip padaryti) taigi laikai sutampa su antros strategijos.

---
Paaiškinimas:
---

Palyginus su antra strategija, deque padalinimo laikas sumažėjo maždaug 30%, vektoriaus liko daugmaž panašus.
Vis dėlto aišku, kad trečioji strategija (savaime suprantama) yra geriausias variantas.

















