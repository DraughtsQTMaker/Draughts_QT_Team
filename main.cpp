#include <QApplication>
#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QTextCodec>
#include <QGridLayout>

#include "mainwindow.h"

int main(int argc, char *argv[]){

    // remote develop branch
    // need to merge

    QApplication a(argc, argv);

    MainWindow mainWin;

    mainWin.showDialog();

    return a.exec();

}
