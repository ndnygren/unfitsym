DO_C_O=g++ -c $(INC_DIR) -Wall
objects= exprLinked.o parserFull.o genAlt.o sumAlt.o subAlt.o prodAlt.o
objects2=sumParse.o subParse.o expParse.o prodParse.o parenParse.o

all: test

test: main.cpp $(objects) $(objects2)
	g++ -Wall main.cpp $(objects) $(objects2) -o test

$(objects2): 
	cp ../parse/*.o ./

exprLinked.o: exprLinked.cpp 
	$(DO_C_O) exprLinked.cpp

parserFull.o: parserFull.cpp 
	$(DO_C_O) parserFull.cpp

genAlt.o: alter/genAlt.cpp 
	$(DO_C_O) alter/genAlt.cpp

sumAlt.o: alter/sumAlt.cpp 
	$(DO_C_O) alter/sumAlt.cpp

subAlt.o: alter/subAlt.cpp 
	$(DO_C_O) alter/subAlt.cpp

prodAlt.o: alter/prodAlt.cpp 
	$(DO_C_O) alter/prodAlt.cpp
