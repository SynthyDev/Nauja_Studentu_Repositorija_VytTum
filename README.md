Kaip naudoti Makefile?
1. Atidarykite aplanką, kurio programą norite paleist (pvz. vector)
2. Būtina turėti MinGW64 arba kitą įrankį, kuris palaiko "make" funkciją: https://gnuwin32.sourceforge.net/packages/make.htm
4. Atidarykite terminalą pasirinktame aplanke.
5. terminale įrašykite šią užklausą: make
6. Paspauskite du kartus pele ant "programa.exe" failo ARBA terminale parašykite programa.exe (priklauso nuo OS).
7. Turėtų iššokti langas, kuriame veiks pasirinkta programa. Joje galite įrašyti parametrus ir pasirinkti programos funkcijas.

---

Versija v1.1
Viskas pakeista į Class tipą.
funkcionalumas tas pats

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

















