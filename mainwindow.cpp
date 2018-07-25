#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QDialog(parent)
{
    // set the size of main window
    this->resize(570,627);

    // set the game version selection dialog
    this->askDialog = new QDialog(0, Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    this->askDialog->resize(300, 150);

    this->firstName= new QLabel("先手:", this->askDialog);
    this->secondName= new QLabel("后手:", this->askDialog);

    this->firstEdit=new QLineEdit(this->askDialog);
    this->firstEdit->setText("F_S_1");

    this->secondEdit=new QLineEdit(this->askDialog);
    this->secondEdit->setText("S_S_1");

    this->labelTex = new QLabel("Please select the version:", this->askDialog);

    this->mode64 = new QRadioButton("64", this->askDialog);
    this->mode100 = new QRadioButton("100", this->askDialog);
    this->mode100->setChecked(true);

    this->confirmBut = new QPushButton("confirm", this->askDialog);
    connect(confirmBut, SIGNAL(clicked()), this, SLOT(accept()));

    this->mainLayout = new QVBoxLayout();
    this->labelLayout = new QHBoxLayout();
    this->playerSideLayout = new QHBoxLayout();
    this->radioLayout = new QHBoxLayout();
    this->butLayout = new QHBoxLayout();

    this->playerSideLayout->addWidget(this->firstName);
    this->playerSideLayout->addWidget(this->firstEdit);
    this->playerSideLayout->addWidget(this->secondName);
    this->playerSideLayout->addWidget(this->secondEdit);

    this->labelLayout->addWidget(this->labelTex);

    this->radioLayout->addWidget(this->mode64);
    this->radioLayout->addWidget(this->mode100);

    this->butLayout->addWidget(this->confirmBut);

    this->mainLayout->addLayout(playerSideLayout);
    this->mainLayout->addLayout(labelLayout);
    this->mainLayout->addLayout(radioLayout);
    this->mainLayout->addLayout(butLayout);

    this->askDialog->setLayout(mainLayout);

}

MainWindow::~MainWindow()
{
}

void MainWindow::showDialog()
{
    // show the version selection dialog
    this->askDialog->show();
}

void MainWindow::accept()
{
    first=firstEdit->text();
    second=secondEdit->text();

    // check the status of radio buttons
    // when 64 version button is checked
    if (this->mode64->isChecked()) {
        this->chessboard = new Chessboard(this,8,this->mode64_layNum);
        this->chessboard->resize(570,627);
        this->chessboard->move(0,0);
        this->askDialog->close();
    }
    // when 100 version button is checked
    else if (this->mode100->isChecked()) {
        this->chessboard = new Chessboard(this,10,this->mode100_layNum);
        this->chessboard->resize(570,627);
        this->chessboard->move(0,0);
        this->askDialog->close();
    }

    // show the main window
    this->show();
}

