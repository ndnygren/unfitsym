DO_C_O=g++ -c $(INC_DIR) -Wall
objects=sumParse.o subParse.o expParse.o 

all: test

test: main.cpp $(objects) 
	g++ -Wall main.cpp $(objects) -o test

sumParse.o: parts/sumParse.cpp 
	$(DO_C_O) parts/sumParse.cpp

subParse.o: parts/subParse.cpp 
	$(DO_C_O) parts/subParse.cpp

expParse.o: parts/expParse.cpp
	$(DO_C_O) parts/expParse.cpp

