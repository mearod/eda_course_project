#include "log.h"

extern MainWindow *mainwindow;

void logOutput(string message,bool isError){
    mainwindow->externLogMessage(message,isError);
};