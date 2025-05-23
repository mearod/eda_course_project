/**
 * @file mainwindow.cpp
 * @copyright MSDA Lab, SJTU
 * @author Limin Hao
 * @date 2024/02/23
 */

#include "mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QtWidgets>

#include "../simulator_interface/simulator_interface.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("MainWindow"));

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();

    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

/**
 * @brief Define and connect the actions.
 * @author Limin Hao
 * @date 2024/02/21
 */
void MainWindow::createActions()
{
    /** @brief file open action */
    fileOpenAction = new QAction(QIcon(":../asset/images/fileopen.png"), tr("open"), this);
    fileOpenAction->setShortcut(Qt::CTRL + Qt::Key_O);
    fileOpenAction->setStatusTip(tr("Open file"));
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

    /** @brief file new action */
    fileNewAction = new QAction(QIcon(":../asset/images/filenew.png"), tr("New"), this);
    fileNewAction->setShortcut(Qt::CTRL + Qt::Key_N);
    fileNewAction->setStatusTip(tr("New file"));
    connect(fileNewAction, SIGNAL(triggered()), this, SLOT(slotNewFile()));

    /** @brief save file action */
    fileSaveAction = new QAction(QPixmap(":../asset/images/filesave.png"), tr("Save"), this);
    fileSaveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    fileSaveAction->setStatusTip(tr("Save file"));
    connect(fileSaveAction, SIGNAL(triggered()), this, SLOT(slotSaveFile()));

    /** @brief cut action */
    cutAction = new QAction(QIcon(":../asset/images/editcut.png"), tr("Cut"), this);
    cutAction->setShortcut(Qt::CTRL + Qt::Key_X);
    cutAction->setStatusTip(tr("Cut to clipboard"));
    connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));

    /** @brief cut action */
    copyAction = new QAction(QIcon(":../asset/images/editcopy.png"), tr("Copy"), this);
    copyAction->setShortcut(Qt::CTRL + Qt::Key_C);
    copyAction->setStatusTip(tr("Copy to clipboard"));
    connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));

    /** @brief cut action */
    pasteAction = new QAction(QIcon(":../asset/images/editpaste.png"), tr("Paste"), this);
    pasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
    pasteAction->setStatusTip(tr("Paste clipboard to selection"));
    connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));

    simulateAction = new QAction(QIcon(":../asset/images/simulate.png"),tr("Simulate"), this);
    simulateAction->setToolTip(tr("simulate current file"));
    connect(simulateAction, SIGNAL(triggered()), this, SLOT(slotSimulate()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    editMenu = menuBar()->addMenu(tr("Edit"));
    simulateMenu = menuBar()->addMenu(tr("Simulate"));

    fileMenu->addAction(fileNewAction);
    fileMenu->addSeparator(); /// Add separator between 2 actions.
    fileMenu->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);

    editMenu->addAction(copyAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);

    simulateMenu->addAction(simulateAction);
}

void MainWindow::createToolBars()
{
    /// You can use multiple toolbars. Actions are separated in the interface.
    fileTool = addToolBar(tr("File"));
    editTool = addToolBar(tr("Edit"));
    simulateTool = addToolBar(tr("Simulate"));

    fileTool->addAction(fileNewAction);
    fileTool->addAction(fileOpenAction);
    fileTool->addAction(fileSaveAction);

    editTool->addAction(copyAction);
    editTool->addAction(cutAction);
    editTool->addAction(pasteAction);

    simulateTool->addAction(simulateAction);
}

/**
 * @brief New action will cover and create a new textedit.
 * @author Limin Hao
 * @date 2024/02/23
 */
void MainWindow::slotNewFile()
{
    textEdit->clear();          /// Clear the text
    textEdit->setHidden(false); /// Display the text.
}

/**
 * @brief Open action will open the saved files
 * @author Limin Hao
 * @date 2024/02/23
 */
void MainWindow::slotOpenFile()
{

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), "spice File (*.sp)");
    /// If the dialog is directly closed, the filename will be null.
    if (fileName == "") {
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"));
            return;
        } else {
            if (!file.isReadable()) {
                QMessageBox::warning(this, tr("Error"), tr("The file is unreadable"));
            } else {
                QTextStream textStream(&file); // Use QTextStream to load text.
                textEdit->setPlainText(textStream.readAll());
                file.close();
            }
        }
    }
}

/**
 * @brief Save action will save the text into a new file when it has not been
 * saved. Otherwise it will be saved in the current file.
 * @author Limin Hao
 * @date 2024/02/23
 */
void MainWindow::slotSaveFile()
{
    statusBar()->showMessage(tr("Saving file..."));

    if (fileName == "") /// File has not been saved.
    {
        /// Text is empty.
        if (textEdit->toPlainText() == "") {
            QMessageBox::warning(this, tr("Warning"), tr("Content cannot be empty!"),
                                 QMessageBox::Ok);
        } else {
            QFileDialog fileDialog;
            fileName = fileDialog.getSaveFileName(this, tr("Open File"), "./", "spice File(*.sp)");
            if (fileName == "") {
                return;
            }
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"),
                                     QMessageBox::Ok);
                return;
            } else {
                /// Create a text stream and pass text in.
                QTextStream textStream(&file);
                QString     str = textEdit->toPlainText();
                textStream << str;
            }
            file.close();
        }
    } else { /// File has been saved.
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Warning"), tr("Failed to open file!"));
            return;
        } else {
            QTextStream textStream(&file);
            QString     str = textEdit->toPlainText();
            textStream << str;
            file.close();
        }
    }
}


void MainWindow::slotSimulate()
{
    QLabel *label = new QLabel();
    label->setText("simulation start!");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font:30px;color:black;background-color:white");
    label->resize(400, 300);
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->show(); // label should be shown to be seen.


    char *fileNameChar;
    QByteArray ba = this->fileName.toLatin1();
    fileNameChar = ba.data();
    startSimulate(fileNameChar);
    label->setText("simulation end!");
}