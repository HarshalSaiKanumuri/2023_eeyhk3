/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QWidget *widget;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QCheckBox *checkBox;

    void setupUi(QDialog *OptionDialog)
    {
        if (OptionDialog->objectName().isEmpty())
            OptionDialog->setObjectName("OptionDialog");
        OptionDialog->resize(511, 418);
        OptionDialog->setSizeGripEnabled(true);
        OptionDialog->setModal(true);
        label = new QLabel(OptionDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 90, 61, 31));
        pushButton = new QPushButton(OptionDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(370, 360, 80, 24));
        lineEdit = new QLineEdit(OptionDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(130, 90, 131, 31));
        label_2 = new QLabel(OptionDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 160, 49, 16));
        label_3 = new QLabel(OptionDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 190, 49, 16));
        label_4 = new QLabel(OptionDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 230, 49, 16));
        horizontalSlider = new QSlider(OptionDialog);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(80, 160, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(OptionDialog);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(79, 190, 161, 20));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(OptionDialog);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(80, 230, 160, 16));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        widget = new QWidget(OptionDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(290, 160, 120, 81));
        widget->setAutoFillBackground(true);
        spinBox = new QSpinBox(OptionDialog);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(240, 160, 42, 25));
        spinBox_2 = new QSpinBox(OptionDialog);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(240, 190, 42, 25));
        spinBox_3 = new QSpinBox(OptionDialog);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(240, 220, 42, 25));
        checkBox = new QCheckBox(OptionDialog);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(30, 280, 151, 21));

        retranslateUi(OptionDialog);
        QObject::connect(horizontalSlider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
        QObject::connect(spinBox, &QSpinBox::valueChanged, horizontalSlider, &QSlider::setValue);
        QObject::connect(horizontalSlider_2, &QSlider::valueChanged, spinBox_2, &QSpinBox::setValue);
        QObject::connect(spinBox_2, &QSpinBox::valueChanged, horizontalSlider_2, &QSlider::setValue);
        QObject::connect(horizontalSlider_3, &QSlider::valueChanged, spinBox_3, &QSpinBox::setValue);
        QObject::connect(spinBox_3, &QSpinBox::valueChanged, horizontalSlider_3, &QSlider::setValue);

        QMetaObject::connectSlotsByName(OptionDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionDialog)
    {
        OptionDialog->setWindowTitle(QCoreApplication::translate("OptionDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("OptionDialog", "Name :", nullptr));
        pushButton->setText(QCoreApplication::translate("OptionDialog", "Save", nullptr));
        label_2->setText(QCoreApplication::translate("OptionDialog", "Red", nullptr));
        label_3->setText(QCoreApplication::translate("OptionDialog", "Green", nullptr));
        label_4->setText(QCoreApplication::translate("OptionDialog", "Blue", nullptr));
        checkBox->setText(QCoreApplication::translate("OptionDialog", "isVisible", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionDialog: public Ui_OptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
