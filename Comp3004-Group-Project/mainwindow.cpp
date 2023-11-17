#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QLabel *processLabel = new QLabel(this);
    processLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QMovie *movie = new QMovie("/home/student/Comp3004-Group-Project/heartRateMonitor.gif");
    processLabel->setMovie(movie);
    processLabel->setGeometry(920,10,152,90);




    movie->start ();












}

MainWindow::~MainWindow()
{
    delete ui;
}

