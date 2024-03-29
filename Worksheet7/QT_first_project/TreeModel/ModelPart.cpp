/**     @file ModelPart.cpp
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Template for model parts that will be added as treeview items
  *
  *     P Evans 2022
  */

#include "ModelPart.h"
#include <vtkSTLReader.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>


/* Commented out for now, will be uncommented later when you have
 * installed the VTK library
 */
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>



ModelPart::ModelPart(const QList<QVariant>& data, ModelPart* parent )
    : m_itemData(data), m_parentItem(parent) {

    /* You probably want to give the item a default colour */
}


ModelPart::~ModelPart() {
    qDeleteAll(m_childItems);
}


void ModelPart::appendChild( ModelPart* item ) {
    /* Add another model part as a child of this part
     * (it will appear as a sub-branch in the treeview)
     */
    item->m_parentItem = this;
    m_childItems.append(item);
}


ModelPart* ModelPart::child( int row ) {
    /* Return pointer to child item in row below this item.
     */
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int ModelPart::childCount() const {
    /* Count number of child items
     */
    return m_childItems.count();
}


int ModelPart::columnCount() const {
    /* Count number of columns (properties) that this item has.
     */
    return m_itemData.count();
}

QVariant ModelPart::data(int column) const {
    /* Return the data associated with a column of this item 
     *  Note on the QVariant type - it is a generic placeholder type
     *  that can take on the type of most Qt classes. It allows each 
     *  column or property to store data of an arbitrary type.
     */
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}


void ModelPart::set(int column, const QVariant &value) {
    /* Set the data associated with a column of this item 
     */
    if (column < 0 || column >= m_itemData.size())
        return;

    m_itemData.replace(column, value);
}


ModelPart* ModelPart::parentItem() {
    return m_parentItem;
}


int ModelPart::row() const {
    /* Return the row index of this item, relative to it's parent.
     */
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ModelPart*>(this));
    return 0;
}
/*
void ModelPart::setColour(const unsigned char R, const unsigned char G, const unsigned char B) {
    // Set the RGB color components of the model part
    m_colorR = R;
    m_colorG = G;
    m_colorB = B;
}
*/


void ModelPart::setColour(int R,int G,int B) {
    // Set the RGB color components of the model part
    m_colorR = R;
    m_colorG = G;
    m_colorB = B;
}

unsigned char ModelPart::getColourR() {
    // Return the red color component of the model part
    return m_colorR;
}

unsigned char ModelPart::getColourG() {
    // Return the green color component of the model part
    return m_colorG;
}

unsigned char ModelPart::getColourB() {
    // Return the blue color component of the model part
    return m_colorB;
}

void ModelPart::setVisible(bool isVisible) {
    // Set the visibility status of the model part
    m_visible = isVisible;
}


bool ModelPart::visible() {
    /* This is a placeholder function that will be used in the next worksheet */
    
    /* As the name suggests ... */
    return m_visible;
}

void ModelPart::loadSTL(QString fileName) {

    /* 1. Use the vtkSTLReader class to load the STL file */
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(fileName.toStdString().c_str());
    reader->Update();

    /* 2. Initialise the part's vtkMapper */
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    /* 3. Initialise the part's vtkActor and link to the mapper */
    vtkNew<vtkActor> actor;

    /* 4. Link the actor to the mapper */
    actor->SetMapper(mapper);

    /* 5. Assign the actor to m_actor */
    m_actor = actor;


    /*  ---- This code was to test out that I could render *.stl files --- Successful !! 1. Stage of Development
    *                                                                      TO DO :     Make it render on MainGUI
    vtkNew<vtkRenderer> renderer;
    //vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("ReadSTL");

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderer->AddActor(actor);

    renderWindow->Render();
    renderWindowInteractor->Start();

    // 2. How can my code find/Get a render window that already exsists...
    */
}


vtkSmartPointer<vtkActor> ModelPart::getActor() {
    /* Needs to return a smart pointer to the vtkActor to allow
     * part to be rendered.
     */
    return m_actor;
}

  //vtkActor* ModelPart::getNewActor() {
    /* This is a placeholder function that will be used in the next worksheet.
     *
     * The default mapper/actor combination can only be used to render the part in
     * the GUI, it CANNOT also be used to render the part in VR. This means you need
     * to create a second mapper/actor combination for use in VR - that is the role
     * of this function. */


     /* 1. Create new mapper */



     /* 2. Create new actor and link to mapper */


     /* 3. Link the vtkProperties of the original actor to the new actor. This means
      *    if you change properties of the original part (colour, position, etc), the
      *    changes will be reflected in the GUI AND VR rendering.
      *
      *    See the vtkActor documentation, particularly the GetProperty() and SetProperty()
      *    functions.
      */


      /* The new vtkActor pointer must be returned here */

  //    return nullptr;

  //}
