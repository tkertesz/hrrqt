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

#OS X konfig
mac:CONFIG += OSXMACHINE

OSXMACHINE {
    INCLUDEPATH += /opt/local/include
    LIBS += -L/opt/local/lib
   #QMAKE_CXXFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
   #QMAKE_LFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
}

#Windows konfig
win32:CONFIG += WINDOWSMACHINE

WINDOWSMACHINE{
    INCLUDEPATH += C://OpenCV//OpenCV_bin//install//include
    LIBS += C://OpenCV//OpenCV_bin//bin//*.dll
}

SOURCES += main.cpp\
        mainwindow.cpp\
        RaceRoad.cpp

HEADERS  += mainwindow.h\
        RaceRoad.hpp\
        Player.hpp

FORMS    += mainwindow.ui

OTHER_FILES += \
    kep.jpg
