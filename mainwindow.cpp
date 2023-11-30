#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    heartRateMonitor = new HeartRateMonitor(ui->horizontalSlider, ui->currHeartRate, this);
    ui->horizontalSlider->setSliderPosition(80);
    drainTimer = new QTimer(this);
    Display *d = new Display(ui->GUIConsole,this);
    processLabel = new QLabel(this);
    processLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    movie = new QMovie("/home/student/Comp3004-Group-Project-main/heartBeat.gif");
    processLabel->setMovie(movie);
    processLabel->setGeometry(920,10,152,90);


    connect(ui->placePad,SIGNAL(released()), this, SLOT(placePad()));
    connect(ui->electrodePadOption, SIGNAL(currentIndexChanged(int)),this, SLOT(bodyType(int)));
    connect(ui->powerOn,SIGNAL(released()), this, SLOT(power()));
    connect(ui->replaceBattery,SIGNAL(released()), this, SLOT(replaceBattery()));
    connect(ui->CPR, SIGNAL(released()), this, SLOT(cprPressed()));
    connect(this,&MainWindow::powerOn, d,&Display::powerOn);
    connect(this,&MainWindow::powerOff, d,&Display::powerOff);
    connect(this,&MainWindow::replaceB, d,&Display::replaceB);
    connect(drainTimer, &QTimer::timeout, this, &MainWindow::drainBattery);

    connect(ui->placePadIncorrectly,SIGNAL(released()), this, SLOT(placePadIncorrectly()));
    connect(ui->shockDelivery, SIGNAL(released()), this, SLOT(shockDelivery()));
    connect(ui->contactShockDelivery, SIGNAL(released()), this, SLOT(patientContactDuringShockDelivery()));



    //heart rate modifier using slider
    //adult HR > 150 / child HR > 200 => shockable rhythm identified
    //prompt to deliver shock
    //press "Shock Delivery" button

    QObject::connect(ui->currHeartRate, &QTextEdit::textChanged, [&]() {
        if (ui->currHeartRate->toPlainText().toInt() > 150){
            if (ui->electrodePadOption->currentText() == "Adult Pads"){
                    movie->setSpeed(ui->currHeartRate->toPlainText().toInt()*2);
                    ui->GUIConsole->clear();
                    ui->GUIConsole->append("SHOCKABLE RHYTHM IDENTIFIED\n");
                    ui->GUIConsole->append("Shock advised\n");
                    ui->shockDelivery->setEnabled(true);
        }
            else {  //child pads selected
                if (ui->currHeartRate->toPlainText().toInt() > 200){
                    movie->setSpeed(ui->currHeartRate->toPlainText().toInt()*2);
                    ui->GUIConsole->clear();
                    ui->GUIConsole->append("SHOCKABLE RHYTHM IDENTIFIED\n");
                    ui->GUIConsole->append("Shock advised\n");
                    ui->shockDelivery->setEnabled(true);
                }
            }
        }

        else if (ui->currHeartRate->toPlainText().toInt() == 149)
        {
            ui->GUIConsole->clear();
        }

        else{
            movie->setSpeed(ui->currHeartRate->toPlainText().toInt()*1.3);
//            ui->GUIConsole->clear();
            ui->shockDelivery->setEnabled(false);
        }

    });


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
    ui->pad1_6->hide();
    ui->pad1_7->hide();

    // ui->CPR->setEnabled(false); //uncomment when ready to test
    ui->shockDelivery->setEnabled(false);
    // ui->placePadIncorrectly->setEnabled(false);
    // ui->contactShockDelivery->setEnabled(false);
    ui->mouthToMouth->setEnabled(false);
    mouthToMouthReady = false;
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
        ui->pad1_6->show();
        ui->pad1_7->show();
    }else{
        ui->padChild1->show();
        ui->padChild2->show();
        ui->padChild3->show();
    }

    ui->GUIConsole->clear();
    ui->GUIConsole->append(padChoice + " Chosen");
}

void MainWindow::bodyType(int index)
{
    if(index  == 0){ //Adult
        ui->GUIConsole->clear();
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
        ui->GUIConsole->clear();
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
        ui->pad1_6->hide();
        ui->pad1_7->hide();

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

void MainWindow::power()
{
   if(ui->powerOn->text() == "Power Off"){
        ui->powerOn->setText("Power On");
        ui->powerOn->setStyleSheet("background-color: rgb(50, 205,50);");
        emit powerOff();
        movie->stop();
        drainTimer->stop();
        processLabel->clear();
        ui->horizontalSlider->setValue(80);
        ui->currHeartRate->setText("--");
        heartRateMonitor->stopOrStartMonitoring();




   }
   else{
        ui->powerOn->setText("Power Off");
        ui->powerOn->setStyleSheet("background-color: rgb(205, 50,50);");
        int PBV = ui->batteryProgressBar->value();
        if( PBV <= 0)
//                ui->powerOn->setText(QString::number(PBV));
                emit replaceB();
        else{
            emit powerOn();
            processLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            processLabel->setMovie(movie);
            processLabel->setGeometry(920,10,152,90);
            movie->setSpeed(100);
            movie->start();
            drainTimer->start(500);
            heartRateMonitor->stopOrStartMonitoring();

        }

   }

}

void MainWindow::replaceBattery(){
    ui->batteryProgressBar->setValue(100);
}

void MainWindow::drainBattery(){
    int currentValue= ui->batteryProgressBar->value();
    if(currentValue > 0){
       ui->batteryProgressBar->setValue(currentValue-1);
        if (currentValue <= 20) {
           ui->GUIConsole->clear();
           ui->GUIConsole->append("BATTERY IS RUNNING LOW! PLEASE REPLACE BATTERY IMMEDIATELY.");
       }
    }else{
        drainTimer->stop();
        disableAllButtons();
        power();
    }
}

void MainWindow::shockTimer(){
    if(padChoice == "Adult Pads"){
        ui->pad1->setStyleSheet("border: 8px solid #555;background-color: rgb(192, 191, 188);border-color: rgb(255, 255, 0);");
        ui->pad1_1->setStyleSheet("border: 8px solid #555;border-color: rgb(255, 255, 0);");
        ui->pad4->setStyleSheet("border: 8px solid #555;background-color: rgb(192, 191, 188);border-color: rgb(255, 255, 0);");
        ui->pad1_5->setStyleSheet("border: 8px solid #555;border-color: rgb(255, 255, 0);");

    }else{
        ui->padChild1->setStyleSheet("border: 8px solid #555;border-color: rgb(255, 255, 0);");
    }
}

void MainWindow::shockTimerDelay(){
    if(padChoice == "Adult Pads"){
        ui->pad1->setStyleSheet("border: 8px solid #555;background-color: rgb(192, 191, 188);border-color: rgb(255, 255, 255);");
        ui->pad1_1->setStyleSheet("border: 2px solid #555;border-color: rgb(255, 255, 255);");
        ui->pad4->setStyleSheet("border: 8px solid #555;background-color: rgb(192, 191, 188);border-color: rgb(255, 255, 255);");
        ui->pad1_5->setStyleSheet("border: 2px solid #555;border-color: rgb(255, 255, 255);");

    }else{
        ui->padChild1->setStyleSheet("background-color: rgb(94, 92, 100);");
    }
}

//for later: a simulation button for someone being in contact with patient when shock is being delivered
//idea: press shock delivery 3 times - 70/30 chance of survival ?
void MainWindow::shockDelivery()
{

    ui->GUIConsole->append("Shock Delivered\n");

    ui->contactShockDelivery->setEnabled(true);

    QTimer::singleShot(0, this, &MainWindow::shockTimer);
    QTimer::singleShot(1000, this, &MainWindow::shockTimerDelay);
    QTimer::singleShot(2000, this, &MainWindow::shockTimer);
    QTimer::singleShot(3000, this, &MainWindow::shockTimerDelay);
    QTimer::singleShot(4000, this, &MainWindow::shockTimer);
    QTimer::singleShot(5000, this, &MainWindow::shockTimerDelay);
}


void MainWindow::patientContactDuringShockDelivery()
{
    ui->GUIConsole->clear();
    ui->GUIConsole->append("PLEASE ENSURE THERE IS NO CONTACT WITH PATIENT WHEN SHOCK IS DELIVERED");
}

void MainWindow::cprPressed()
{
    // ui->GUIConsole->clear();
    ui->GUIConsole->append("Performing CPR");
    checkForMouthToMouthPress();
}

//here, set mouthtomouthready bool var to true
//for every 10 cpr presses, check if press mouth to mouth was pressed once and only once
//if mouth to mouth is pressed after 10 cpr presses, clear console and call performMouthtoMouth()
    //flash green light on the indicator if this happens
//if mouth to mouth not pressed after 10 cpr presses, display msg on gui saying it was not performed
    //flash red light on the indicator if this happens

void MainWindow::checkForMouthToMouthPress()
{
    QString guiText = ui->GUIConsole->toPlainText();
    int cprCounter = guiText.count("Performing CPR");

    if (cprCounter == 10){
        mouthToMouthReady = true;
        ui->mouthToMouth->setEnabled(true);
    }
    else if (cprCounter > 10) {
        ui->GUIConsole->clear();
        ui->GUIConsole->append("YOU DID NOT DO MOUTH TO MOUTH.");
    }
}


void MainWindow::performMouthtoMouth()  //press mouth to mouth button
{
    ui->mouthToMouth->setEnabled(false);
    ui->GUIConsole->clear();
    ui->GUIConsole->append("Performing mouth to mouth..");
}


void MainWindow::disableAllButtons()
{
    ui->placePad->setEnabled(false);
    ui->shockDelivery->setEnabled(false);
    ui->CPR->setEnabled(false);
    ui->mouthToMouth->setEnabled(false);
    ui->horizontalSlider->setDisabled(true);
    ui->electrodePadOption->setEnabled(false);
    ui->placePadIncorrectly->setDisabled(true);
    ui->contactShockDelivery->setDisabled(true);

}

void MainWindow::AEDInitialLightUp()
{
    QTime dieTime= QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    ui->checkResponseIndc->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(220, 20, 60)");
    LightUpDelay();
    ui->checkResponseIndc->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;");
    ui->call911Indc->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(220, 20, 60)");
    LightUpDelay();
    ui->call911Indc->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;");
    ui->padPlacedIndc->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(220, 20, 60)");


}

void MainWindow::LightUpDelay()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}








