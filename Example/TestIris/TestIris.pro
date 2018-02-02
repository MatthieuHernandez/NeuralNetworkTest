#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T14:15:25
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

TARGET = TestIris
TEMPLATE = app

CONFIG += c++14

QMAKE_CXXFLAGS += /O2

SOURCES += main.cpp \
    mainwindow.cpp \

HEADERS += mainwindow.h \

FORMS += mainwindow.ui

if(msvc) {
    message("MSVC")
    QMAKE_CXXFLAGS += /O2
}
if(mingw) {
    message("MinGW")
    QMAKE_CXXFLAGS += -O3
}

INCLUDEPATH += $$PWD\
               "$$PWD\..\..\src" \

include("$$PWD\..\..\src\NeuralNetwork.pro")

Matthieu {

    INCLUDEPATH += "C:/Qt/5.10.0/msvc2015_64/bin" \
                   "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/include" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/shared" \
                   "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt" \

    LIBS += -lpsapi \
}

nutsxy {

}
