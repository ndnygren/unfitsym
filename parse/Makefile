DO_C_O=g++ -c $(INC_DIR) -Wall
objects=sumParse.o expParse.o 

all: test

test: main.cpp $(objects) 
	g++ -Wall main.cpp $(objects) -o test
	rm *.o 

sumParse.o: parts/sumParse.cpp 
	$(DO_C_O) parts/sumParse.cpp

expParse.o: parts/expParse.cpp
	$(DO_C_O) parts/expParse.cpp
