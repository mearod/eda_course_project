/**
 * @file mainwindow.h
 * @author Limin Hao
 * @date 2024/02/21
 * @brief Defination for class and functions
 * @ref https://doc.qt.io/qt-5/qmainwindow.html
 * @copyright MSDA Lab, SJTU
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSplitter>
#include <string>

using namespace std;



class QAction;
class QMenu;
class QToolBar;
class QTextEdit;
class QWidget;
class QTextStream;

/**
 * @class MainWindow
 * @brief QMainWindow definition
 * @author Limin Hao
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    private:
    void logMessage(const QString &message, bool isError);

    public:
    void externLogMessage(string message, bool isError);

    public:
    /** @brief constructor */
    MainWindow(QWidget *parent = 0);
    /** @brief deconstructor */
    ~MainWindow();
    /** @brief All of the menus should be defined in this function*/
    void createMenus();
    /** @brief All of the actions should be defined in this function*/
    void createActions();
    /** @brief All of the toolbars should be defined in this function*/
    void createToolBars();

public slots:
    void slotNewFile();
    void slotOpenFile();
    void slotSaveFile();

    void slotSimulateOP();
    void slotSimulateDC();
    void slotSimulateAC();
    void slotSimulateTRAN();

private:
    QMenu    *fileMenu;
    QMenu    *editMenu;
    QMenu    *simulateMenu;

    QToolBar *fileTool;
    QToolBar *editTool;

    QToolBar *simulateTool;

    QAction *fileOpenAction;
    QAction *fileNewAction;
    QAction *fileSaveAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    QAction *simulateOPAction;
    QAction *simulateDCAction;
    QAction *simulateACAction;
    QAction *simulateTRANAction;

    QTextEdit *textEdit;
    QTextEdit *logTextEdit;

    QSplitter *splitter;

    QString fileName = "";
};

#endif // MAINWINDOW_H

