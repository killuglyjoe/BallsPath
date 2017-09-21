CONFIG -= qt
CONFIG += c++11

TARGET = BallsPath
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Utils/point.cpp \
    Utils/ballspathcommandlineparser.cpp \
    Utils/gamemap.cpp \
    Utils/itemball.cpp

HEADERS += \
    Utils/point.h \
    Utils/ballspathcommandlineparser.h \
    Utils/gamemap.h \
    Utils/itemball.h
