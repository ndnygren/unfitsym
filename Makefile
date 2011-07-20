#############################################################################
# Makefile for building: unfitsym
# Generated by qmake (2.01a) (Qt 4.2.1) on: Wed Jul 20 13:18:01 2011
# Project:  unfitsym.pro
# Template: app
# Command: /usr/lib/qt4/bin/qmake -unix -o Makefile unfitsym.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
LEX           = flex
YACC          = yacc
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
LEXFLAGS      = 
YACCFLAGS     = -d
INCPATH       = -I/usr/lib/qt4/mkspecs/linux-g++ -I. -I/usr/lib/qt4/include/QtCore -I/usr/lib/qt4/include/QtCore -I/usr/lib/qt4/include/QtGui -I/usr/lib/qt4/include/QtGui -I/usr/lib/qt4/include -I. -Iparse -Iparse/parts -Iparse/nodes -Ieqnsearch -Ieqnsearch/alter -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/qt4/lib -lQtGui -L/usr/lib/mysql -lpng -lSM -lICE -lXi -lXrender -lXrandr -lXcursor -lXinerama -lfreetype -lfontconfig -lXext -lX11 -lQtCore -lz -lm -ldl -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		MainUFSearchWindow.cpp \
		eqnsearch/exprLinked.cpp \
		eqnsearch/generateProof.cpp \
		parse/parserFull.cpp \
		eqnsearch/alter/derivAlt.cpp \
		eqnsearch/alter/fracAlt.cpp \
		eqnsearch/alter/genAlt.cpp \
		eqnsearch/alter/hatAlt.cpp \
		eqnsearch/alter/negAlt.cpp \
		eqnsearch/alter/prodAlt.cpp \
		eqnsearch/alter/subAlt.cpp \
		eqnsearch/alter/sumAlt.cpp \
		parse/parts/cassetteMachine.cpp \
		parse/parts/curlyParse.cpp \
		parse/parts/derivParse.cpp \
		parse/parts/expParse.cpp \
		parse/parts/fracParse.cpp \
		parse/parts/hatParse.cpp \
		parse/parts/negParse.cpp \
		parse/parts/parenParse.cpp \
		parse/parts/prodParse.cpp \
		parse/parts/subParse.cpp \
		parse/parts/sumParse.cpp moc_MainUFSearchWindow.cpp
OBJECTS       = main.o \
		MainUFSearchWindow.o \
		exprLinked.o \
		generateProof.o \
		parserFull.o \
		derivAlt.o \
		fracAlt.o \
		genAlt.o \
		hatAlt.o \
		negAlt.o \
		prodAlt.o \
		subAlt.o \
		sumAlt.o \
		cassetteMachine.o \
		curlyParse.o \
		derivParse.o \
		expParse.o \
		fracParse.o \
		hatParse.o \
		negParse.o \
		parenParse.o \
		prodParse.o \
		subParse.o \
		sumParse.o \
		moc_MainUFSearchWindow.o
DIST          = /usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/g++.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/release.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		unfitsym.pro
QMAKE_TARGET  = unfitsym
DESTDIR       = 
TARGET        = unfitsym

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: unfitsym.pro  /usr/lib/qt4/mkspecs/linux-g++/qmake.conf /usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/g++.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/release.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/lib/libQtGui.prl \
		/usr/lib/qt4/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile unfitsym.pro
/usr/lib/qt4/mkspecs/common/unix.conf:
/usr/lib/qt4/mkspecs/common/g++.conf:
/usr/lib/qt4/mkspecs/common/linux.conf:
/usr/lib/qt4/mkspecs/qconfig.pri:
/usr/lib/qt4/mkspecs/features/qt_functions.prf:
/usr/lib/qt4/mkspecs/features/qt_config.prf:
/usr/lib/qt4/mkspecs/features/exclusive_builds.prf:
/usr/lib/qt4/mkspecs/features/default_pre.prf:
/usr/lib/qt4/mkspecs/features/release.prf:
/usr/lib/qt4/mkspecs/features/default_post.prf:
/usr/lib/qt4/mkspecs/features/warn_on.prf:
/usr/lib/qt4/mkspecs/features/qt.prf:
/usr/lib/qt4/mkspecs/features/unix/thread.prf:
/usr/lib/qt4/mkspecs/features/moc.prf:
/usr/lib/qt4/mkspecs/features/resources.prf:
/usr/lib/qt4/mkspecs/features/uic.prf:
/usr/lib/qt4/lib/libQtGui.prl:
/usr/lib/qt4/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile unfitsym.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/unfitsym1.0.0 || $(MKDIR) .tmp/unfitsym1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/unfitsym1.0.0/ && $(COPY_FILE) --parents MainUFSearchWindow.h eqnsearch/eqnMetric.h eqnsearch/exprLinked.h eqnsearch/generateProof.h eqnsearch/isolateMetric.h eqnsearch/isoSimpMetric.h eqnsearch/searchMaxMin.h parse/parserFull.h eqnsearch/alter/derivAlt.h eqnsearch/alter/fracAlt.h eqnsearch/alter/genAlt.h eqnsearch/alter/hatAlt.h eqnsearch/alter/negAlt.h eqnsearch/alter/prodAlt.h eqnsearch/alter/subAlt.h eqnsearch/alter/sumAlt.h parse/nodes/binOpNode.h parse/nodes/derivNode.h parse/nodes/eqnNode.h parse/nodes/fracNode.h parse/nodes/hatNode.h parse/nodes/leafNode.h parse/nodes/negNode.h parse/nodes/nodeTypes.h parse/nodes/numNode.h parse/nodes/prodNode.h parse/nodes/subNode.h parse/nodes/sumNode.h parse/nodes/varNode.h parse/parts/altParse.h parse/parts/cassetteMachine.h parse/parts/curlyParse.h parse/parts/derivParse.h parse/parts/expParse.h parse/parts/fracParse.h parse/parts/hatParse.h parse/parts/multiTokParse.h parse/parts/natParse.h parse/parts/negParse.h parse/parts/parenParse.h parse/parts/parsePart.h parse/parts/prodParse.h parse/parts/seqParse.h parse/parts/subParse.h parse/parts/sumParse.h parse/parts/tokParse.h parse/parts/varParse.h .tmp/unfitsym1.0.0/ && $(COPY_FILE) --parents main.cpp MainUFSearchWindow.cpp eqnsearch/exprLinked.cpp eqnsearch/generateProof.cpp parse/parserFull.cpp eqnsearch/alter/derivAlt.cpp eqnsearch/alter/fracAlt.cpp eqnsearch/alter/genAlt.cpp eqnsearch/alter/hatAlt.cpp eqnsearch/alter/negAlt.cpp eqnsearch/alter/prodAlt.cpp eqnsearch/alter/subAlt.cpp eqnsearch/alter/sumAlt.cpp parse/parts/cassetteMachine.cpp parse/parts/curlyParse.cpp parse/parts/derivParse.cpp parse/parts/expParse.cpp parse/parts/fracParse.cpp parse/parts/hatParse.cpp parse/parts/negParse.cpp parse/parts/parenParse.cpp parse/parts/prodParse.cpp parse/parts/subParse.cpp parse/parts/sumParse.cpp .tmp/unfitsym1.0.0/ && (cd `dirname .tmp/unfitsym1.0.0` && $(TAR) unfitsym1.0.0.tar unfitsym1.0.0 && $(COMPRESS) unfitsym1.0.0.tar) && $(MOVE) `dirname .tmp/unfitsym1.0.0`/unfitsym1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/unfitsym1.0.0


yaccclean:
lexclean:
clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


/usr/lib/qt4/bin/moc:
	(cd $(QTDIR)/src/tools/moc && $(MAKE))

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainUFSearchWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainUFSearchWindow.cpp
moc_MainUFSearchWindow.cpp: MainUFSearchWindow.h \
		/usr/lib/qt4/bin/moc
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) MainUFSearchWindow.h -o moc_MainUFSearchWindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_image_collection_clean compiler_moc_source_clean compiler_uic_clean 

####### Compile

main.o: main.cpp parse/parserFull.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h \
		eqnsearch/searchMaxMin.h \
		eqnsearch/exprLinked.h \
		eqnsearch/eqnMetric.h \
		eqnsearch/isoSimpMetric.h \
		eqnsearch/isolateMetric.h \
		eqnsearch/generateProof.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

MainUFSearchWindow.o: MainUFSearchWindow.cpp MainUFSearchWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainUFSearchWindow.o MainUFSearchWindow.cpp

exprLinked.o: eqnsearch/exprLinked.cpp eqnsearch/exprLinked.h \
		eqnsearch/eqnMetric.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o exprLinked.o eqnsearch/exprLinked.cpp

generateProof.o: eqnsearch/generateProof.cpp eqnsearch/generateProof.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o generateProof.o eqnsearch/generateProof.cpp

parserFull.o: parse/parserFull.cpp parse/parserFull.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parserFull.o parse/parserFull.cpp

derivAlt.o: eqnsearch/alter/derivAlt.cpp eqnsearch/alter/derivAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o derivAlt.o eqnsearch/alter/derivAlt.cpp

fracAlt.o: eqnsearch/alter/fracAlt.cpp eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fracAlt.o eqnsearch/alter/fracAlt.cpp

genAlt.o: eqnsearch/alter/genAlt.cpp eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o genAlt.o eqnsearch/alter/genAlt.cpp

hatAlt.o: eqnsearch/alter/hatAlt.cpp eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hatAlt.o eqnsearch/alter/hatAlt.cpp

negAlt.o: eqnsearch/alter/negAlt.cpp eqnsearch/alter/negAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o negAlt.o eqnsearch/alter/negAlt.cpp

prodAlt.o: eqnsearch/alter/prodAlt.cpp eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o prodAlt.o eqnsearch/alter/prodAlt.cpp

subAlt.o: eqnsearch/alter/subAlt.cpp eqnsearch/alter/subAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o subAlt.o eqnsearch/alter/subAlt.cpp

sumAlt.o: eqnsearch/alter/sumAlt.cpp eqnsearch/alter/sumAlt.h \
		eqnsearch/alter/genAlt.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/subNode.h \
		parse/nodes/prodNode.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/nodes/fracNode.h \
		parse/nodes/negNode.h \
		parse/nodes/hatNode.h \
		parse/nodes/derivNode.h \
		eqnsearch/alter/subAlt.h \
		eqnsearch/alter/prodAlt.h \
		eqnsearch/alter/fracAlt.h \
		eqnsearch/alter/negAlt.h \
		eqnsearch/alter/hatAlt.h \
		eqnsearch/alter/derivAlt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sumAlt.o eqnsearch/alter/sumAlt.cpp

cassetteMachine.o: parse/parts/cassetteMachine.cpp parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cassetteMachine.o parse/parts/cassetteMachine.cpp

curlyParse.o: parse/parts/curlyParse.cpp parse/parts/curlyParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o curlyParse.o parse/parts/curlyParse.cpp

derivParse.o: parse/parts/derivParse.cpp parse/parts/derivParse.h \
		parse/nodes/derivNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o derivParse.o parse/parts/derivParse.cpp

expParse.o: parse/parts/expParse.cpp parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o expParse.o parse/parts/expParse.cpp

fracParse.o: parse/parts/fracParse.cpp parse/parts/fracParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/fracNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fracParse.o parse/parts/fracParse.cpp

hatParse.o: parse/parts/hatParse.cpp parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/nodes/binOpNode.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hatParse.o parse/parts/hatParse.cpp

negParse.o: parse/parts/negParse.cpp parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o negParse.o parse/parts/negParse.cpp

parenParse.o: parse/parts/parenParse.cpp parse/parts/parenParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parenParse.o parse/parts/parenParse.cpp

prodParse.o: parse/parts/prodParse.cpp parse/parts/prodParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/prodNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/parts/tokParse.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o prodParse.o parse/parts/prodParse.cpp

subParse.o: parse/parts/subParse.cpp parse/parts/subParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/subNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/sumParse.h \
		parse/nodes/sumNode.h \
		parse/parts/tokParse.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o subParse.o parse/parts/subParse.cpp

sumParse.o: parse/parts/sumParse.cpp parse/parts/sumParse.h \
		parse/nodes/eqnNode.h \
		parse/nodes/nodeTypes.h \
		parse/nodes/sumNode.h \
		parse/nodes/binOpNode.h \
		parse/parts/expParse.h \
		parse/parts/cassetteMachine.h \
		parse/parts/parsePart.h \
		parse/parts/natParse.h \
		parse/parts/multiTokParse.h \
		parse/parts/seqParse.h \
		parse/nodes/numNode.h \
		parse/nodes/leafNode.h \
		parse/parts/subParse.h \
		parse/nodes/subNode.h \
		parse/parts/varParse.h \
		parse/nodes/varNode.h \
		parse/parts/prodParse.h \
		parse/nodes/prodNode.h \
		parse/parts/parenParse.h \
		parse/parts/curlyParse.h \
		parse/parts/fracParse.h \
		parse/nodes/fracNode.h \
		parse/parts/negParse.h \
		parse/nodes/negNode.h \
		parse/parts/tokParse.h \
		parse/parts/hatParse.h \
		parse/nodes/hatNode.h \
		parse/parts/derivParse.h \
		parse/nodes/derivNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sumParse.o parse/parts/sumParse.cpp

moc_MainUFSearchWindow.o: moc_MainUFSearchWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainUFSearchWindow.o moc_MainUFSearchWindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

