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
            simulator_interface/simulator_interface.h \
            spice_command/command_plot.h \
            result_recorder/result_recorder.h \
            plotter/qcustomplot/qcustomplot.h \
            plotter/plotter.h



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
           simulator_interface/simulator_interface.cpp \
           result_recorder/result_recorder.cpp \
           spice_command/command_plot.cpp \
           plotter/plotter.cpp \
           plotter/qcustomplot/qcustomplot.cpp
           
RESOURCES += mainwindow/mainwindow.qrc

LIBS += -larmadillo -llapack -lblas -lfl -ly
