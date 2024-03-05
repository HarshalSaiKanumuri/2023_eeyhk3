#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "optiondialog.h"
#include "./ui_optiondialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set context menu policy to Actions Context Menu
    ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);

    // Create and add action for item options
    QAction* itemOptionsAction = new QAction("Item Options", this);
    ui->treeView->addAction(itemOptionsAction);
    connect(itemOptionsAction, &QAction::triggered, this, &MainWindow::on_actionItemOptions_triggered);

    // Connect the statusUpdateMessage() signal to the showMessage() slot of the status bar
    connect(this, &MainWindow::statusUpdateMessage,
        ui->statusBar, &QStatusBar::showMessage);

    // Connect the released() signal of the addButton object to the handleAddButton slot in this object
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton_editter);

    // Create/allocate the ModelList
    this->partList = new ModelPartList("Parts List");

    // Link it to the tree view in the GUI
    ui->treeView->setModel(this->partList);

    // Manually create a model tree
    ModelPart* rootItem = this->partList->getRootItem();
    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");
        ModelPart* childItem = new ModelPart({ name, visible });
        rootItem->appendChild(childItem);
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");
            ModelPart* childChildItem = new ModelPart({ name, visible });
            childItem->appendChild(childChildItem);
        }
    }

    // Connect the clicked() signal of when user clicks on the Tree Viewer
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    emit statusUpdateMessage(QString("Add button was clicked"), 0);
    QMessageBox msgBox;
    msgBox.setText("Add button was clicked");
    msgBox.exec();
}

void MainWindow::handleButton_editter() {
    // Get the index of the selected item
    QModelIndex index = ui->treeView->currentIndex();

    // Get a pointer to the item from the index
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    // In this case, we will retrieve the name string from the internal QVariant data array
    QString text = selectedPart->data(0).toString();

    // Create the OptionDialog and pass the selectedPart as an argument
    OptionDialog dialog(selectedPart, this); // Pass the selectedPart and the parent widget (this)

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted"), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}

void MainWindow::handleTreeClicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
    QMessageBox msgBox;
    msgBox.setText("The selected item is: " + text);
    msgBox.exec();
}

void MainWindow::on_actionOpen_File_triggered()
{
    emit statusUpdateMessage(QString("Open File action triggered"), 0);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
    );
    emit statusUpdateMessage(QString("Selected file: ") + fileName, 0);
}

void MainWindow::on_actionItemOptions_triggered()
{
    // Get the index of the selected item
    QModelIndex index = ui->treeView->currentIndex();

    // Get a pointer to the item from the index
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    // In this case, we will retrieve the name string from the internal QVariant data array
    QString text = selectedPart->data(0).toString();

    // Create the OptionDialog and pass the selectedPart as an argument
    OptionDialog dialog(selectedPart, this); // Pass the selectedPart and the parent widget (this)

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted"), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}
