#-------------------------------------------------
#
# Project created by QtCreator 2013-10-11T12:34:59
#
#-------------------------------------------------
cache();
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HungarianRoadRage
TEMPLATE = app

#OS X config
macx:CONFIG += OSXMACHINE

OSXMACHINE {

    message("***Using settings for Mac OS X***")

    #To copy images directory
    APP_IMAGE_FILES.files = images
    APP_IMAGE_FILES.path = Contents/MacOS/debug

    QMAKE_BUNDLE_DATA += APP_IMAGE_FILES

    INCLUDEPATH += /opt/local/include

    LIBS += -L/opt/local/lib \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
        #-lopencv_objdetect \
        #-lopencv_contrib \
        #-lopencv_calib3d \
        #-lopencv_features2d \
        #-lopencv_flann \
        #-lopencv_gpu \
        #-lopencv_legacy \
        #-lopencv_nonfree \
        #-lopencv_ml \
        #-lopencv_photo \
        #-lopencv_video \
        #-lopencv_videostab \
        #-lopencv_stitching \
        #-lopencv_superres \
        #-lopencv_ts

   #QMAKE_CXXFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
   #QMAKE_LFLAGS = -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.7
}

#Windows config
win32:CONFIG += WINDOWSMACHINE

WINDOWSMACHINE{

    message("***Using settings for Windows***")

    #To copy images directory
    APP_IMAGE_FILES.files = images
    APP_IMAGE_FILES.path = def

    QMAKE_BUNDLE_DATA += APP_IMAGE_FILES

    INCLUDEPATH += C://OpenCV//OpenCV_bin//install//include
    LIBS += C://OpenCV//OpenCV_bin//bin//*.dll
}

#Other files:

SOURCES += main.cpp\
        mainwindow.cpp\
        RaceRoad.cpp

HEADERS  += mainwindow.h\
        RaceRoad.hpp\
        Player.hpp \
    network.hpp

FORMS    += mainwindow.ui

OTHER_FILES += images/*

# Megjegyzesek:
# Amiket kikommenteltem az OS X konfigban, azok nem kellenek egyelore, windows-nal is szerkesszetek be
# a *.dll helyett mindig azokat a LIB-eket csak, amik kellenek. Felesleges dolgokat ne forgassunk bele
