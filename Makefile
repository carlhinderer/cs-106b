CC=g++
FLAGS=-Wall -g
VERSION=-std=c++14 
RM=rm
ANYEXE=-f *.exe

SAMPLETARGET=sample.exe
SAMPLEMAIN=./samplecode/powertab.cpp

STANFORDLIBS=./lib/StanfordCPPLib

samplemake:
	$(CC) $(FLAGS) -o $(SAMPLETARGET) $(SAMPLEMAIN) $(VERSION)

clean:
	$(RM) $(ANYEXE)