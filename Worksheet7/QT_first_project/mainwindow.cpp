#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "optiondialog.h"
#include "./ui_optiondialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCylinder.h>
#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include "TreeModel/ModelPart.h"      // Include the header file  ModelPart

// Required headers at the top 
#include <vtkSTLReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>



/* Commented out for now, will be uncommented later when you have
 * installed the VTK library
 */
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>

//--------------------------------------------------------------------------------------------------------------
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

    /* This needs adding to MainWindow constructor */
    /* Link a render window with the Qt widget */
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    /* Add a renderer */
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    /* Create an object and add to renderer (this will change later to display a CAD model) */
    /* Will just copy and paste cylinder example from before */
    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e., in practice an octagonal prism).
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are
    // defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    /* Reset Camera (probably needs to go in its own function that is called whenever
model is changed) */

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

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
    openFile();
}


//--------------------------------------------------------------------
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)") // allows .stl files and .txt files
    );

    if (fileName.isEmpty()) {
        // User cancelled file selection
        return;
    }

    emit statusUpdateMessage(QString("Selected file: ") + fileName, 0);

    // Obtain the pointer to the root item of the model tree
    ModelPart* parentItem = this->partList->getRootItem();

    // Create the child item
    QString name = fileName;
    QString visible = "true";
    ModelPart* childItem = new ModelPart({ name, visible });

    // Append the child item to the root item
    parentItem->appendChild(childItem);
    //m_selectedPart->getColourR()

    ui->treeView->reset(); // required to make it show up

    // Load STL file and obtain actor from childItem
    childItem->loadSTL(fileName);


    // Get the actor from the selected item
    vtkSmartPointer<vtkActor> actor = childItem->getActor();

    /*
    // Create a new renderer, render window, and render window interactor
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("ReadSTL");

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    */

    // Add the actor to the renderer
    renderer->AddActor(actor);

    renderWindow->Render();

    
}


//--------------------------------------------------------------------

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

void MainWindow::updateRender() {
    renderer->RemoveAllViewProps();
    updateRenderFromTree(partList->index(0, 0, QModelIndex()));
    renderer->Render();
}

void MainWindow::updateRenderFromTree(const QModelIndex& index) {
    if (index.isValid()) {
        ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());
        /* Retrieve actor from selected part and add to renderer */
        // Add your logic here to retrieve the actor from the selected part and add it to the renderer
    }

    /* Check to see if this part has any children */
    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) {
        return;
    }

    /* Loop through children and add their actors */
    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}
