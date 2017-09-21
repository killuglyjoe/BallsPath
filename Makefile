MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -std=gnu++0x -Wall -W -fPIC $(DEFINES)
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = BallsPath1.0.0
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		Utils/point.cpp \
		Utils/ballspathcommandlineparser.cpp \
		Utils/gamemap.cpp \
		Utils/itemball.cpp 
OBJECTS       = main.o \
		point.o \
		ballspathcommandlineparser.o \
		gamemap.o \
		itemball.o

QMAKE_TARGET  = BallsPath
DESTDIR       = 
TARGET        = BallsPath


first: all
####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: 

all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Sub-libraries

check: first

benchmark: first

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

main.o: main.cpp Utils/ballspathcommandlineparser.h \
		Utils/point.h \
		Utils/gamemap.h \
		Utils/itemball.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

point.o: Utils/point.cpp Utils/point.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o point.o Utils/point.cpp

ballspathcommandlineparser.o: Utils/ballspathcommandlineparser.cpp Utils/ballspathcommandlineparser.h \
		Utils/point.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ballspathcommandlineparser.o Utils/ballspathcommandlineparser.cpp

gamemap.o: Utils/gamemap.cpp Utils/gamemap.h \
		Utils/itemball.h \
		Utils/point.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gamemap.o Utils/gamemap.cpp

itemball.o: Utils/itemball.cpp Utils/itemball.h \
		Utils/point.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o itemball.o Utils/itemball.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

