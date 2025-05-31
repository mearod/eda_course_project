TEMPLATE = app
TARGET = Y-SPICE
INCLUDEPATH += $$PWD/src

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

HEADERS +=  src/analyser/analyser.h \
            src/circuit/circuit.h \
            src/circuit/node.h \
            src/devices/device.h \
            src/mainwindow/mainwindow.h \
            src/parser/parser.hpp \
            src/parser/scanner.hpp \
            src/simulator_interface/simulator_interface.h \
            src/spice_command/command_plot.h \
            src/spice_command/command_ac.h \
            src/spice_command/command_dc.h \
            src/spice_command/command_tran.h \
            src/result_recorder/result_recorder.h \
            src/plotter/qcustomplot/qcustomplot.h \
            src/plotter/plotter.h \
            src/function_generator/function_generator.h



SOURCES +=  src/main.cpp \
            src/analyser/analyser.cpp \
            src/circuit/circuit.cpp \
            src/devices/capacitor.cpp \
            src/devices/cccs.cpp \
            src/devices/ccvs.cpp \
            src/devices/cs.cpp \
            src/devices/device.cpp \
            src/devices/inductor.cpp \
            src/devices/resistor.cpp \
            src/devices/vccs.cpp \
            src/devices/vcvs.cpp \
            src/devices/vs.cpp \
            src/mainwindow/mainwindow.cpp \
            src/parser/parser.cpp \
            src/parser/scanner.cpp \
            src/simulator_interface/simulator_interface.cpp \
            src/result_recorder/result_recorder.cpp \
            src/plotter/plotter.cpp \
            src/plotter/qcustomplot/qcustomplot.cpp \
            src/function_generator/pulse.cpp \
            src/function_generator/sin.cpp

           
RESOURCES += src/mainwindow/mainwindow.qrc

LIBS += -larmadillo -llapack -lblas -lfl -ly

PRE_TARGETDEPS += flexBison

# 添加代码行数统计目标
code_line_count.target = linecount
code_line_count.commands = find . -type f \\( -name \"*.cpp\" \
                          -o -name \"*.lex\" \
                          -o -name \"*.yy\" \
                          -o -name \"*.h\" \\) \
                         ! -name \"qcustomplot.cpp\" \
                         ! -name \"qcustomplot.h\" \
                         ! -name \"parser.cpp\" \
                         ! -name \"parser.hpp\" \
                         ! -name \"scanner.cpp\" \
                         ! -name \"scanner.hpp\" \
                         ! -name \"moc_*.*\" \
                         ! -name \"qrc_*.*\" \
                         -print0 | xargs -0 wc -l

code_line_count.depends = FORCE
QMAKE_EXTRA_TARGETS += code_line_count


# flex\bison target
flex_bison.target = flexBison
flex_bison.commands = make -C ./src/parser flex_bison_output
flex_bison.depends = FORCE
QMAKE_EXTRA_TARGETS += flex_bison
