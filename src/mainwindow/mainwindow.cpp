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
    setWindowTitle(tr("Y-SPICE"));

    // 创建主分割器
    splitter = new QSplitter(Qt::Vertical, this); // 垂直分割

    textEdit = new QTextEdit(this);
    
// 创建日志分组框
QGroupBox *logGroupBox = new QGroupBox(tr("Y-HSPICE Log Output"), this);
logGroupBox->setAlignment(Qt::AlignCenter);  // 设置标题居中
logGroupBox->setStyleSheet(
    "QGroupBox {"
    "   border: 1px solid gray;"
    "   border-radius: 3px;"
    "   margin-top: 10px;"
    "   padding-top: 10px;"
    "   font-weight: bold;"
    "}"
    "QGroupBox::title {"
    "   subcontrol-origin: margin;"
    "   left: 10px;"
    "   padding: 0 3px;"
    "}"
);

QVBoxLayout *logLayout = new QVBoxLayout(logGroupBox);
logTextEdit = new QTextEdit(this);
logTextEdit->setReadOnly(true); // 日志窗口只能读取，不能编辑
logLayout->addWidget(logTextEdit);
logGroupBox->setLayout(logLayout);


    // 将两个部件添加到分割器中
    splitter->addWidget(textEdit);
    splitter->addWidget(logGroupBox); // 添加分组框而不是直接添加日志窗口

    // 设置分割器的初始比例（例如：文本编辑区占70%，日志区占30%）
    QList<int> sizes;
    sizes << height() * 0.7 << height() * 0.3;
    splitter->setSizes(sizes);

    // 设置分割器为中央部件
    setCentralWidget(splitter);

    createActions();
    createMenus();
    createToolBars();

    resize(800, 600);
}


MainWindow::~MainWindow()
{
}

void MainWindow::logMessage(const QString &message, bool isError = false) {
    QTextCursor cursor(logTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    
    // 设置文本颜色
    QTextCharFormat format;
    format.setForeground(isError ? Qt::red : Qt::black);
    cursor.setCharFormat(format);
    
    // 添加时间戳和消息
    QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss]");
    cursor.insertText(QString("[Y-SPICE]%1 %2\n").arg(timestamp).arg(message));
    
    // 自动滚动到底部
    logTextEdit->ensureCursorVisible();
}

void MainWindow::externLogMessage(string message, bool isError) {
    logMessage(QString::fromStdString(message), isError);
}

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

    simulateOPAction = new QAction(QIcon(":../asset/images/simulate.png"),tr("Simulate OP"), this);
    simulateOPAction->setToolTip(tr("simulate current file with OP"));
    connect(simulateOPAction, SIGNAL(triggered()), this, SLOT(slotSimulateOP()));
    
    simulateDCAction = new QAction(QIcon(":../asset/images/simulate.png"),tr("Simulate DC"), this);
    simulateDCAction->setToolTip(tr("simulate current file with DC"));
    connect(simulateDCAction, SIGNAL(triggered()), this, SLOT(slotSimulateDC()));

    simulateACAction = new QAction(QIcon(":../asset/images/simulate.png"),tr("Simulate AC"), this);
    simulateACAction->setToolTip(tr("simulate current file with AC"));
    connect(simulateACAction, SIGNAL(triggered()), this, SLOT(slotSimulateAC()));

    simulateTRANAction = new QAction(QIcon(":../asset/images/simulate.png"),tr("Simulate TRAN"), this);
    simulateTRANAction->setToolTip(tr("simulate current file with TRAN"));
    connect(simulateTRANAction, SIGNAL(triggered()), this, SLOT(slotSimulateTRAN()));
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

    simulateMenu->addAction(simulateOPAction);
    simulateMenu->addAction(simulateDCAction);
    simulateMenu->addAction(simulateACAction);
    simulateMenu->addAction(simulateTRANAction);
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

    simulateTool->addAction(simulateDCAction);
    simulateTool->addAction(simulateACAction);
    simulateTool->addAction(simulateTRANAction);
}

/**
 * @brief New action will cover and create a new textedit.
 * @author Limin Hao
 * @date 2024/02/23
 */
void MainWindow::slotNewFile()
{
    logMessage("Creating new file");
    textEdit->clear();
    textEdit->setHidden(false);
    fileName = "";
}

/**
 * @brief Open action will open the saved files
 * @author Limin Hao
 * @date 2024/02/23
 */
void MainWindow::slotOpenFile()
{
    logMessage("Attempting to open file...");
    
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), "spice File (*.sp)");
    if (fileName == "") {
        logMessage("File open dialog canceled by user");
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            logMessage(QString("Failed to open file: %1").arg(fileName), true);
            QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"));
            return;
        } else {
            if (!file.isReadable()) {
                logMessage(QString("File is unreadable: %1").arg(fileName), true);
                QMessageBox::warning(this, tr("Error"), tr("The file is unreadable"));
            } else {
                QTextStream textStream(&file);
                textEdit->setPlainText(textStream.readAll());
                file.close();
                logMessage(QString("Successfully opened file: %1").arg(fileName));
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
    logMessage("Attempting to save file...");
    statusBar()->showMessage(tr("Saving file..."));

    if (fileName == "") {
        if (textEdit->toPlainText() == "") {
            logMessage("Cannot save empty content", true);
            QMessageBox::warning(this, tr("Warning"), tr("Content cannot be empty!"),
                               QMessageBox::Ok);
        } else {
            fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./", "spice File(*.sp)");
            if (fileName == "") {
                logMessage("File save dialog canceled by user");
                return;
            }
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                logMessage(QString("Failed to save file: %1").arg(fileName), true);
                QMessageBox::warning(this, tr("Error"), tr("Failed to open file!"),
                                   QMessageBox::Ok);
                return;
            } else {
                QTextStream textStream(&file);
                QString str = textEdit->toPlainText();
                textStream << str;
                file.close();
                logMessage(QString("Successfully saved file: %1").arg(fileName));
            }
        }
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            logMessage(QString("Failed to save file: %1").arg(fileName), true);
            QMessageBox::warning(this, tr("Warning"), tr("Failed to open file!"));
            return;
        } else {
            QTextStream textStream(&file);
            QString str = textEdit->toPlainText();
            textStream << str;
            file.close();
            logMessage(QString("Successfully saved file: %1").arg(fileName));
        }
    }
}

void MainWindow::slotSimulateOP()
{
    logMessage("OP simulation started.");

    char *fileNameChar;
    QByteArray ba = this->fileName.toLatin1();
    fileNameChar = ba.data();
    startOPSimulate(fileNameChar);

    
    logMessage("OP simulation ended.");
}
void MainWindow::slotSimulateDC()
{
    logMessage("DC simulation started.");


    char *fileNameChar;
    QByteArray ba = this->fileName.toLatin1();
    fileNameChar = ba.data();
    startDCSimulate(fileNameChar);

    
    logMessage("DC simulation ended.");
}

void MainWindow::slotSimulateAC()
{
    logMessage("AC simulation started.");

    char *fileNameChar;
    QByteArray ba = this->fileName.toLatin1();
    fileNameChar = ba.data();
    startACSimulate(fileNameChar);
    
    logMessage("AC simulation ended.");
}

void MainWindow::slotSimulateTRAN()
{
    logMessage("TRAN simulation started.");

    char *fileNameChar;
    QByteArray ba = this->fileName.toLatin1();
    fileNameChar = ba.data();
    startTRANSimulate(fileNameChar);

    logMessage("TRAN simulation ended.");
}