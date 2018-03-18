#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T05:59:12
#
#-------------------------------------------------

QT += core
QT += gui
QT += widgets

TARGET = NeuralNetwork

TEMPLATE = app

CONFIG += console
CONFIG += c++14



SOURCES += \
    $$PWD/neuralNetwork.cpp \
    $$PWD/perceptron.cpp \
    $$PWD/neuralNetworkGettersAndSetters.cpp \
    $$PWD/layer.cpp \
    $$PWD/alltoall.cpp

HEADERS += $$PWD/perceptron.h \
    $$PWD/neuralNetwork.h \
    $$PWD/activationfunctions.h \
    $$PWD/layer.h \
    $$PWD/alltoall.h

Matthieu {

INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt" \

QMAKE_LIBDIR += "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um/x64/" \
                "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/ucrt/x64" \

INCLUDEPATH += "C:/Qt/5.10.0/msvc2015_64/bin" \
               "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/include" \
               "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/shared" \
               "C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt" \
               "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/um" \

QMAKE_CFLAGS_RELEASE += /MT
QMAKE_CXXFLAGS_RELEASE += /MT

QMAKE_CFLAGS_DEBUG += /MTd
QMAKE_CXXFLAGS_DEBUG += /MTd

CONFIG(release, debug|release) {

    QMAKE_CXXFLAGS += /O2
    QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:msvcrt.lib \

}
CONFIG(debug, debug|release) {

    QMAKE_CXXFLAGS += /O0
    DEFINES += _DEBUG
    QMAKE_LFLAGS_DEBUG   += /NODEFAULTLIB:msvcrtd.lib \
                            /NODEFAULTLIB:libcmt.lib
}

}
