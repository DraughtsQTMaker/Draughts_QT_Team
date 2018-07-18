#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLayout>
#include <QInputDialog>

#include "chessboard.h"

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    ~MainWindow();

    // the dialog to select game version (64 or 100)
    QDialog* askDialog;

    // show game version selection dialog
    void showDialog();

private:
    // information text of version selection dialog
    QLabel* labelTex;
    QLabel* firstName;
    QLabel* secondName;
    QLineEdit* firstEdit;
    QLineEdit* secondEdit;

    // version selection radio buttons
    // version 64
    QRadioButton* mode64;
    // version 100
    QRadioButton* mode100;

    // confirm button on version selection dialog
    QPushButton* confirmBut;

    // layouts of version selection dialog
    QVBoxLayout* mainLayout;
    QHBoxLayout* labelLayout;
    QHBoxLayout* radioLayout;
    QHBoxLayout* butLayout;

    // the chessboard object on the main window
    Chessboard* chessboard;

    // the layer number of searching
    // layer number of version 64
    const int mode64_layNum = 8;
    // layer number of version 100
    const int mode100_layNum = 11;

public slots:
    virtual void accept();

};

#endif // MAINWINDOW_H
