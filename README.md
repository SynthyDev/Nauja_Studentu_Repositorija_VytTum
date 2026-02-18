**Kodo paaiškinimas versijai v0.1**

KODO ESMĖ:
Studentų bei pavardžių suvedimo ir generavimo sistema. 
Visi reikalavimai (lygtais) atitikti. 
Yra galimybė suvesti visus duomenis ranka, pusiau ranka, arba visiškai atsitiktinai sugeneruoti.
Paskaičiuojamas įvestų studentų pažymių vidurkis bei mediana.
Parodomas sąrašas studentų bei kiekvieno jų vidurkiai.

FUNKCIJOS:
inputas() ir randominputas() // priklausomai nuo pasirinkto įvesties būdo, leidžia vartotojui įvesti norimus studentus bei pažymius.
Vector faile studentų ir pažymių kiekis nelimituojamas. Masyvų faile programos pradžioje inicializuojamas maksimalus jų skaičius.
outputas() // į console išrašomi visi studentai (jų vardas bei pavardė) bei vidurkiai (normalus vidurkis bei mediana).
lytgen() // sugeneruoja arba "mot" arba "vyr" lytį. Naudojama atsitiktiniam vardų generavimui, kad būtų nuspręsta studento lytis
Priklausomai nuo sugeneruojamos lyties skiriasi parametras randomvardas() ir randompavarde() funkcijoms.
randomvardas() // sugeneruojamas atsitiktinis vardas iš vektoriaus fvardai arba mvardai, priklausomai nuo lyties.
randompavarde() // sugeneruojama atsitiktinė pavardė iš vektoriaus pavardes. Priklausomai nuo lyties, "prikabinama" galūnė.

BENDRA LOGIKA:
Pasirenkamas įvesties būdas -> atitinkamai paleidžiama arba atsitiktinio arba rankinio generavimo funkcija, arba programa nutraukiama ->
-> sugeneruojami arba įvedami vardai bei pažymiai -> apskaičiuojamas vidurkis, surikiuojami vektoriai, randama mediana ->
-> atspausdinami duomenys apie kiekvieną studentą.
