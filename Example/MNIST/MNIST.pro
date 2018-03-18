#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T15:28:09
#
#-------------------------------------------------

QT += core gui

QT += widgets # greaterThan(QT_MAJOR_VERSION, 4):


QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MNIST
TEMPLATE = app

CONFIG += c++14

SOURCES += $$PWD/main.cpp \
        $$PWD/mainwindow.cpp \
        $$PWD/data.cpp \
        $$PWD/../../lib/qcustomplot.cpp \


HEADERS += mainwindow.h\
           data.h\
           $$PWD/../../lib/qcustomplot.h

INCLUDEPATH += $$PWD \
               $$PWD/../../src \
               $$PWD/../../lib \

FORMS += \
        mainwindow.ui

if(msvc) {
    message("MSVC")
    QMAKE_CXXFLAGS += /O2
}
if(mingw) {
    message("MinGW")
    QMAKE_CXXFLAGS += -O3
}

include("$$PWD/../../src/NeuralNetwork.pro")

Matthieu {

    INCLUDEPATH += "C:/Qt/5.10.0/msvc2015_64/bin" \
                   "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/include" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/shared" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/um" \

    LIBS += -lpsapi \

    message("compile configuration for Matthieu")
}

nutsxy {

    INCLUDEPATH += "C:/Programming/Qt/5.6/mingw49_32/bin" \

    message("compile configuration for NUTSXY")
}

