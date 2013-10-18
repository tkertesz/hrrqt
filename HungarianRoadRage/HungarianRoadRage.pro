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
CONFIG += MYHOTOSXMACHINE

MYHOTOSXMACHINE {
    INCLUDEPATH += /opt/local/include/
    LIBS += -L/opt/local/lib/
}

SOURCES += main.cpp\
        mainwindow.cpp\
        RaceRoad.cpp

HEADERS  += mainwindow.h\
        RaceRoad.hpp\
        Player.hpp

FORMS    += mainwindow.ui
