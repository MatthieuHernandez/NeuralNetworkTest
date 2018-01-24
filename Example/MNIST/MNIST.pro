#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T15:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MNIST
TEMPLATE = app

#DEFINES += QT_DEPRECATED_WARNINGS

Matthieu {

    include("$$PWD\..\..\src\NeuralNetwork.pro")

    INCLUDEPATH += $$PWD\
                   "$$PWD\..\..\src" \
                   "C:/Qt/5.10.0/msvc2015_64/bin" \
                   "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/include" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/shared" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt" \

    #LIBS += C:\Program Files (x86)\Windows Kits\10\Lib\10.0.16299.0\um\x64\shell32.lib

    SOURCES += \
            ../MNIST/main.cpp \
            mainwindow.cpp

    HEADERS += \
            mainwindow.h

    FORMS += \
            mainwindow.ui

    LIBS += -lpsapi \

    if(msvc) {
        message("MSVC")
        QMAKE_CXXFLAGS += /O2
    }
    if(mingw) {
        message("MinGW")
        QMAKE_CXXFLAGS += -O3
    }
}

SOURCES += \
    data.cpp

HEADERS += \
    data.h
