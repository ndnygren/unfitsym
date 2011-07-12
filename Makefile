DO_C_O=g++ -c $(INC_DIR) -Wall
objects=parserFull.o sumParse.o subParse.o expParse.o prodParse.o parenParse.o fracParse.o
objects2= exprLinked.o genAlt.o sumAlt.o subAlt.o prodAlt.o fracAlt.o generateProof.o

all: libufparse.a libufsearch.a unfit unfitgui

unfit: main.cpp eqnsearch/searchMaxMin.cpp
	g++ -o unfit main.cpp -lufparse -lufsearch -L.

unfitgui: guimain.cpp ufForm.cpp eqnsearch/generateProof.h
	g++ `pkg-config --cflags --libs gtkmm-2.4` -o unfitgui guimain.cpp -lufparse -lufsearch -L.

libufparse.a: $(objects) 
	ar cq libufparse.a $(objects)

libufparse.so: $(objects) 
	ld -G -o libufparse.so $(objects)

libufsearch.a: $(objects2) 
	ar cq libufsearch.a $(objects2)

libufsearch.so: $(objects2) 
	ld -G -o libufsearch.so $(objects2)



parserFull.o: parse/parserFull.cpp 
	$(DO_C_O) parse/parserFull.cpp

sumParse.o: parse/parts/sumParse.cpp 
	$(DO_C_O) parse/parts/sumParse.cpp

subParse.o: parse/parts/subParse.cpp 
	$(DO_C_O) parse/parts/subParse.cpp

prodParse.o: parse/parts/prodParse.cpp 
	$(DO_C_O) parse/parts/prodParse.cpp

expParse.o: parse/parts/expParse.cpp
	$(DO_C_O) parse/parts/expParse.cpp

parenParse.o: parse/parts/parenParse.cpp
	$(DO_C_O) parse/parts/parenParse.cpp

fracParse.o: parse/parts/fracParse.cpp
	$(DO_C_O) parse/parts/fracParse.cpp


exprLinked.o: eqnsearch/exprLinked.cpp 
	$(DO_C_O) eqnsearch/exprLinked.cpp

genAlt.o: eqnsearch/alter/genAlt.cpp 
	$(DO_C_O) eqnsearch/alter/genAlt.cpp

sumAlt.o: eqnsearch/alter/sumAlt.cpp 
	$(DO_C_O) eqnsearch/alter/sumAlt.cpp

subAlt.o: eqnsearch/alter/subAlt.cpp 
	$(DO_C_O) eqnsearch/alter/subAlt.cpp

prodAlt.o: eqnsearch/alter/prodAlt.cpp 
	$(DO_C_O) eqnsearch/alter/prodAlt.cpp

fracAlt.o: eqnsearch/alter/fracAlt.cpp 
	$(DO_C_O) eqnsearch/alter/fracAlt.cpp

generateProof.o: eqnsearch/generateProof.cpp 
	$(DO_C_O) eqnsearch/generateProof.cpp

clean: 
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f unfit
	rm -f unfitgui
