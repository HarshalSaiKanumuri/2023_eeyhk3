#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TreeModel/ModelPart.h"      // Include the header file  ModelPart
#include "TreeModel/ModelPartList.h"  // Include the  file for ModelPartList


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Example of slot definition in mainwindow.h
    // Add this to the MainWindow class definition
public slots:
    void handleButton();
    void handleTreeClicked();
    void on_actionOpen_File_triggered();

    // Example of signal definition in mainwindow.h
    // This needs adding to the MainWindow class definition
signals:
    void statusUpdateMessage(const QString &message, int timeout);

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;
};
#endif // MAINWINDOW_H
