/**
 * @file main.cpp
 * @brief The main entrance
 * @author Limin Hao
 * @date 2024/02/23
 * @copyright MSDA Lab, SJTU
 */

#include "src/mainwindow/mainwindow.h"
#include <QApplication>

MainWindow *mainwindow;

int main(int argc, char **args)
{
    QApplication app(argc, args);

    mainwindow = new MainWindow;
    mainwindow->show();

    return app.exec();
}