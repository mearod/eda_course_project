/**
 * @file main.cpp
 * @brief The main entrance
 * @author Limin Hao
 * @date 2024/02/23
 * @copyright MSDA Lab, SJTU
 */

#include "mainwindow/mainwindow.h"
#include <QApplication>

int main(int argc, char **args)
{
    QApplication app(argc, args);

    MainWindow *mainwindow = new MainWindow;
    mainwindow->show();

    return app.exec();
}