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
    connect(ui->electrodePadOption, SIGNAL(currentIndexChanged(int)),this, SLOT(bodyType(int)));

    connect(ui->placePadIncorrectly,SIGNAL(released()), this, SLOT(placePadIncorrectly()));



    ui->padChild1->hide();
    ui->padChild2->hide();
    ui->padChild3->hide();

    ui->pad1->hide();
    ui->pad2->hide();
    ui->pad3->hide();
    ui->pad4->hide();
    ui->pad1_1->hide();
    ui->pad1_2->hide();
    ui->pad1_3->hide();
    ui->pad1_4->hide();
    ui->pad1_5->hide();

    ui->CPR->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::placePad()
{
   padChoice = ui->electrodePadOption->currentText();
    if(padChoice == "Adult Pads"){
        ui->pad1->show();
        ui->pad2->show();
        ui->pad3->show();
        ui->pad4->show();
        ui->pad1_1->show();
        ui->pad1_2->show();
        ui->pad1_3->show();
        ui->pad1_4->show();
        ui->pad1_5->show();
    }else{
        ui->padChild1->show();
        ui->padChild2->show();
        ui->padChild3->show();
    }

    ui->GUIConsole->append(padChoice + " Chosen");
}


void MainWindow::bodyType(int index)
{
    if(index  == 0){ //Adult
        ui->GUIConsole->append("Adult Chosen");
        ui->padChild1->hide();
        ui->padChild2->hide();
        ui->padChild3->hide();

        ui->BoobLeft->show();
        ui->BoobRight->show();
        ui->ab1->show();
        ui->ab2->show();
        ui->ab3->show();
        ui->ab4->show();
        ui->ab5->show();
        ui->ab6->show();

    }else{ //Child
        ui->GUIConsole->append("Child Chosen");
        ui->pad1->hide();
        ui->pad2->hide();
        ui->pad3->hide();
        ui->pad4->hide();
        ui->pad1_1->hide();
        ui->pad1_2->hide();
        ui->pad1_3->hide();
        ui->pad1_4->hide();
        ui->pad1_5->hide();

        ui->BoobLeft->hide();
        ui->BoobRight->hide();
        ui->ab1->hide();
        ui->ab2->hide();
        ui->ab3->hide();
        ui->ab4->hide();
        ui->ab5->hide();
        ui->ab6->hide();
    }
}

void MainWindow::placePadIncorrectly()
{
    padChoice = ui->electrodePadOption->currentText();
    if(padChoice == "Adult Pads"){

    }else{

    }

    ui->GUIConsole->clear();
    ui->GUIConsole->append(padChoice + " are placed Incorrectly");
    ui->GUIConsole->append("Please place correctly");

}

//adult HR > 150 / child HR > 200 => shockable rhythm identified
//prompt to deliver shock
//press "Shock Delivery" button
//for later: a simulation button for someone being in contact with patient when shock is being delivered
void MainWindow::shockDelivery()
{


}






