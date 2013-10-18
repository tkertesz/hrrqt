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

CONFIG += MYHOTOSXMACHINE

MYHOTOSXMACHINE {
    INCLUDEPATH += /opt/local/include/
    LIBS += -L/opt/local/lib/
}

SOURCES += main.cpp\
        mainwindow.cpp \
    RaceRode.cpp

HEADERS  += mainwindow.h \
    RaceRode.hpp \
    Player.hpp

FORMS    += mainwindow.ui
