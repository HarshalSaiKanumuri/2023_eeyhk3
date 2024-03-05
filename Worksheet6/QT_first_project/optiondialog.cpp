#include "optiondialog.h"
#include "ui_optiondialog.h"
#include "TreeModel/ModelPart.h" // Include the header file for ModelPart
#include <QDebug>
#include <QMessageBox>
#include <qspinbox.h>
#include <QSpinBox>

OptionDialog::OptionDialog(ModelPart* selectedPart, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
    , m_selectedPart(selectedPart)
{
    ui->setupUi(this);
    


    // Populate the UI elements with the current values of the selected ModelPart
    ui->lineEdit->setText(selectedPart->data(0).toString()); //  column 0 is for the name
    // You can similarly populate other UI elements for color, visibility, etc.

// Set initial values for color and visibility directly
    ui->spinBox->setValue(m_selectedPart->getColourR());
    ui->spinBox_2->setValue(m_selectedPart->getColourG());
    ui->spinBox_3->setValue(m_selectedPart->getColourB());
    ui->checkBox->setChecked(m_selectedPart->visible());

    // Connect the textChanged signal of the QLineEdit to the updateName slot
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &OptionDialog::updateName);

    // Connect signals from input elements to slots for color and visibility updates
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateColor()));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(updateColor()));  //  spinBox_2 is for green
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(updateColor())); // Assuming SpinBox_3 is for blue
    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(updateVisibility()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRedValue(int)));

}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::updateName()
{
    QString name = ui->lineEdit->text();

    // Update the name of the selected ModelPart
    m_selectedPart->set(0, name); // Assuming column 0 is for the name

    // Do something with the name value (e.g., update a label)
}

void OptionDialog::updateColor()
{
    int red = ui->spinBox->value();
    int green = ui->spinBox_2->value();
    int blue = ui->spinBox_3->value();

    // Update the color of the selected ModelPart
    m_selectedPart->setColour(red, green, blue);
    
}

void OptionDialog::updateVisibility()
{
    bool isVisible = ui->checkBox->isChecked();

    // Update the visibility of the selected ModelPart
    m_selectedPart->setVisible(isVisible);

}


void OptionDialog::updateUIFromModel()
{
    // Set initial values for color and visibility
    ui->spinBox->setValue(m_selectedPart->getColourR());
    ui->spinBox_2->setValue(m_selectedPart->getColourG());
    ui->spinBox_3->setValue(m_selectedPart->getColourB());
    ui->checkBox->setChecked(m_selectedPart->visible());

    // Set initial value for the name
    ui->lineEdit->setText(m_selectedPart->data(0).toString());
}

void OptionDialog::updateRedValue(int value)
{
    // Convert the integer value to a string and set it as the text of lineEdit_2
    ui->lineEdit_2->setText(QString::number(value));
}

/*
#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}
*/
