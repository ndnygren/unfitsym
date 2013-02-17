parserfiles = break-words.o parserFull.o lnParse.o hatParse.o sumParse.o idParse.o sineParse.o subParse.o curlyParse.o derivParse.o cassetteMachine.o tvarParse.o idxParse.o parenParse.o expParse.o cosineParse.o dParse.o fracParse.o prodParse.o intParse.o negParse.o

all: svgplot

break-words.o: ../parse/break-words.cpp
	g++ -c -Wall ../parse/break-words.cpp

parserFull.o: ../parse/parserFull.cpp
	g++ -c -Wall ../parse/parserFull.cpp

lnParse.o: ../parse/parts/lnParse.cpp
	g++ -c -Wall ../parse/parts/lnParse.cpp

hatParse.o: ../parse/parts/hatParse.cpp
	g++ -c -Wall ../parse/parts/hatParse.cpp

sumParse.o: ../parse/parts/sumParse.cpp
	g++ -c -Wall ../parse/parts/sumParse.cpp

idParse.o: ../parse/parts/idParse.cpp
	g++ -c -Wall ../parse/parts/idParse.cpp

sineParse.o: ../parse/parts/sineParse.cpp
	g++ -c -Wall ../parse/parts/sineParse.cpp

subParse.o: ../parse/parts/subParse.cpp
	g++ -c -Wall ../parse/parts/subParse.cpp

curlyParse.o: ../parse/parts/curlyParse.cpp
	g++ -c -Wall ../parse/parts/curlyParse.cpp

derivParse.o: ../parse/parts/derivParse.cpp
	g++ -c -Wall ../parse/parts/derivParse.cpp

cassetteMachine.o: ../parse/parts/cassetteMachine.cpp
	g++ -c -Wall ../parse/parts/cassetteMachine.cpp

tvarParse.o: ../parse/parts/tvarParse.cpp
	g++ -c -Wall ../parse/parts/tvarParse.cpp

idxParse.o: ../parse/parts/idxParse.cpp
	g++ -c -Wall ../parse/parts/idxParse.cpp

parenParse.o: ../parse/parts/parenParse.cpp
	g++ -c -Wall ../parse/parts/parenParse.cpp

expParse.o: ../parse/parts/expParse.cpp
	g++ -c -Wall ../parse/parts/expParse.cpp

cosineParse.o: ../parse/parts/cosineParse.cpp
	g++ -c -Wall ../parse/parts/cosineParse.cpp

dParse.o: ../parse/parts/dParse.cpp
	g++ -c -Wall ../parse/parts/dParse.cpp

fracParse.o: ../parse/parts/fracParse.cpp
	g++ -c -Wall ../parse/parts/fracParse.cpp

prodParse.o: ../parse/parts/prodParse.cpp
	g++ -c -Wall ../parse/parts/prodParse.cpp

intParse.o: ../parse/parts/intParse.cpp
	g++ -c -Wall ../parse/parts/intParse.cpp

negParse.o: ../parse/parts/negParse.cpp
	g++ -c -Wall ../parse/parts/negParse.cpp

main.o: main.cpp configLoader.h  eqnScaler.h  svgFactory.h
	g++ -c -Wall main.cpp

svgplot: ${parserfiles} main.o
	g++ -Wall -o svgplot main.o ${parserfiles}
