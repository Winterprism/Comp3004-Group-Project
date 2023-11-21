#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QLabel *processLabel = new QLabel(this);
    processLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QMovie *movie = new QMovie("/home/student/Comp3004-Group-Project-main/heartRateMonitor.gif");
    processLabel->setMovie(movie);
    processLabel->setGeometry(920,10,152,90);
    movie->start ();


    connect(ui->placePad,SIGNAL(released()), this, SLOT(placePad()));









}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::placePad()
{
    ui->pad1->setStyleSheet("background-color: rgb(50, 205,50);");
    ui->pad2->setStyleSheet("background-color: rgb(50, 205,50);");
    ui->pad3->setStyleSheet("background-color: rgb(50, 205,50);");


    padChoice = ui->electrodePadOption->currentText();

    ui->GUIConsole->append(padChoice);


}


void MainWindow::bodyType()
{
    if (ui->electrodePadOption->currentText() == "adult"){
        ui->GUIConsole->append("adult");
    }else{
        ui->GUIConsole->append("child");
    }


}

