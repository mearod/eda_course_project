TEMPLATE = app
TARGET = test
INCLUDEPATH += $$PWD

QT += widgets printsupport

CONFIG += debug
#CONFIG += release

CONFIG(debug, release|debug) {
    message("Compiling in debug mode.")
}

CONFIG(release, release|debug) {
    message("Compiling in release mode.")
}

macx{
    CONFIG -= sdk_no_version_check
    CONFIG -= app_bundle
    message("Compiling on macOS.")
}

MOC_DIR     = build
OBJECTS_DIR = build
RCC_DIR     = build
UI_DIR      = build

HEADERS += analyser/analyser.h \
            circuit/circuit.h \
            circuit/node.h \
            devices/device.h \
            mainwindow/mainwindow.h \
            parser/parser.hpp \
            parser/scanner.hpp \
            simulator_interface/simulator_interface.h

SOURCES += main.cpp \
           analyser/analyser.cpp \
           circuit/circuit.cpp \
           devices/capacitor.cpp \
           devices/cccs.cpp \
           devices/ccvs.cpp \
           devices/cs.cpp \
           devices/device.cpp \
           devices/inductor.cpp \
           devices/resistor.cpp \
           devices/vccs.cpp \
           devices/vcvs.cpp \
           devices/vs.cpp \
           mainwindow/mainwindow.cpp \
           parser/parser.cpp \
           parser/scanner.cpp \
           simulator_interface/simulator_interface.cpp

RESOURCES += mainwindow/mainwindow.qrc

LIBS += -larmadillo -llapack -lblas -lfl -ly
