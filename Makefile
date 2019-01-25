CC=g++
FLAGS=-Wall -g
VERSION=-std=c++14 
RM=rm
ANYEXE=-f *.exe

SAMPLETARGET=sample.exe
SAMPLEMAIN=./samplecode/powertab.cpp

STANFORDLIBS=./lib/StanfordCPPLib
IOLIB=./lib/StanfordCPPLib/io
PRIVATELIB=./lib/StanfordCPPLib/private

samplemake:
	$(CC) $(FLAGS) -o $(SAMPLETARGET) $(SAMPLEMAIN) \
	$(VERSION) -I $(IOLIB) -I $(PRIVATELIB) -I $(STANFORDLIBS)

clean:
	$(RM) $(ANYEXE)