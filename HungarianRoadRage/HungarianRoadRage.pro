#-------------------------------------------------
#
# Project created by QtCreator 2013-10-11T12:34:59
#
#-------------------------------------------------
cache();
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HungarianRoadRage
TEMPLATE = app
#
# For Open CV and etc.
#
CONFIG += OSXMACHINE

OSXMACHINE {
    INCLUDEPATH += /opt/local/include
    LIBS += -L/opt/local/lib

    #QMAKE_CXXFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
    #QMAKE_LFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
}

SOURCES += main.cpp\
        mainwindow.cpp\
        RaceRoad.cpp

HEADERS  += mainwindow.h\
        RaceRoad.hpp\
        Player.hpp

FORMS    += mainwindow.ui
