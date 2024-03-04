#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "optiondialog.h"
#include "./ui_optiondialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>

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

    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton_editter);

    /* Create/allocate the ModelList */
    this->partList = new ModelPartList("Parts List");

    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);

    /* Manually create a model tree - there are much better and more flexible ways of doing this,
   e.g., with nested functions. This is just a quick example as a starting point. */
    ModelPart *rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart *childItem = new ModelPart({name, visible});

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart *childChildItem = new ModelPart({name, visible});

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }

    // Connect the clicked() signal of when user clicks on the Tree Viewer
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);  // edit for ex5 4.3.2



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

void MainWindow::handleButton_editter() {
    // This causes MainWindow to emit the signal that will then be
    // received by the status bar's slot

    OptionDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted"), 0);
    } else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}

void MainWindow::handleTreeClicked() {

    // Get the index of the selected item
    QModelIndex index = ui->treeView->currentIndex();

    // Get a pointer to the item from the index
    ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());

    // In this case, we will retrieve the name string from the internal QVariant data array
    QString text = selectedPart->data(0).toString();

    // Emit a status update message
    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);

    QMessageBox msgBox;
    msgBox.setText("The selected item is: " + text);
    msgBox.exec();

}

// Slot function added to MainWindow.cpp
void MainWindow::on_actionOpen_File_triggered() {
    // Add this line of code so you can see if the action is working
    emit statusUpdateMessage(QString("Open File action triggered"), 0);
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );
    emit statusUpdateMessage(QString("Selected file: ") + fileName, 0);

}
