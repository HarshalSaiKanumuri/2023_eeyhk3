#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the statusUpdateMessage() signal to the showMessage() slot of the status bar
    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusBar, &QStatusBar::showMessage);
    // Example of connecting signals and slots in mainwindow.cpp
    // Add the following lines at the end of the MainWindow constructor

    // Connect the released() signal of the addButton object to the handleAddButton slot in this object
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    // This causes MainWindow to emit the signal that will then be
    // received by the status bar's slot
    emit statusUpdateMessage(QString("Add button was clicked"), 0);

    QMessageBox msgBox;
    msgBox.setText("Add button was clicked");
    msgBox.exec();
}
