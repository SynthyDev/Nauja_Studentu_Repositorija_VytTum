programa: versija_v3.0.cpp funk.cpp studentai_res.o
	g++ versija_v3.0.cpp funk.cpp studentai_res.o -o programa

studentai_res.o: studentai.rc studentai.manifest
	windres studentai.rc -O coff -o studentai_res.o

cleanexe:
	del /Q programa.exe
	del /Q testai.exe

cleantxt:
	del /Q *.txt

Test:
	g++ testing.cpp funk.cpp -o testai

Runtest:
	./testai
