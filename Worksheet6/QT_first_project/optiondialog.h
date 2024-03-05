/*#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
*/
#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "TreeModel/ModelPart.h" // Include the header file for ModelPart

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(ModelPart* selectedPart, QWidget *parent = nullptr); // Constructor with ModelPart pointer
    ~OptionDialog();
    void updateName();
    void updateColor();
    void updateVisibility();
    void updateUIFromModel();

    void updateRedValue(int value);

private:
    Ui::OptionDialog *ui;
    ModelPart* m_selectedPart; // Pointer to the selected ModelPart
};

#endif // OPTIONDIALOG_H
