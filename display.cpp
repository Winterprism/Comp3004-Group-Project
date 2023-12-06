#include "display.h"

Display::Display(QTextEdit *display, QObject *parent):QObject(parent), d(display), currentStep(0),interrupt(false){
}

void Display::powerOn(){
    d->setText("Powering On\n");
    steps << "Battery Capacity: "
          << "Defibrillation Electrodes Connection: "
          << "ECG Circuitry: "
          << "Defibrillator Charge and Discharge Circuitry: "
          << "Microprocessor Hardware/Software: "
          << "CPR Circuitry and Sensor: "
          << "Audio Circuitry: ";

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Display::updateDisplay);
    timer->start(1000);
    if(!interrupt)
    QTimer::singleShot(8000,this,&Display::call911);
    if(!interrupt)
    QTimer::singleShot(11000,this,&Display::placePad);
}
void Display::electrodesCheck(){
    if(!interrupt)
    d->setText("Electrodes Are Correctly Placed\n");
}
void Display::batteriesCheck(){
    if(!interrupt)
    d->setText("Batteries are installed");
}


void Display::powerOff(){
    interrupt = true;
    timer->stop();
    d->setText("Powering Off\n");
}


void Display::replaceB(){
    if(!interrupt)
    d->setText("Batteries need to be replaced");
}


void Display::responsivenesCheck(){
    d->clear();
    d->setText("Checking for responsiveness...");
}

void Display::call911(){
    d->clear();
    if(!interrupt)
    d->setText("Calling 911...");
}

void Display::placePad(){
    d->clear();
    if(!interrupt)
    d->setText("Please place the correct pad");
    interrupt = false;
}

void Display::stable(){
    d->clear();
    if(!interrupt)
    d->setText("The patient is stable ");
}
void Display::startSelfTest(){
        currentStep = 0;
        d->clear(); // Clear previous text
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Display::updateDisplay);
        timer->start(1000); // Delay of 1 second between updates

}

void Display::updateDisplay() {
        if (currentStep < steps.size()) {
            QString currentText = d->toPlainText();
            currentText += steps[currentStep] + "Completed\n";
            d->setPlainText(currentText);
            currentStep++;
        } else {
            timer->stop();
        }
    }


void Display::heartIsStopped()
{
    d->clear();
    d->setText("PATIENT'S HEART IS STOPPED!!!");
}
