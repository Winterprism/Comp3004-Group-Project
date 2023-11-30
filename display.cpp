#include "display.h"

Display::Display(QTextEdit *display, QObject *parent):QObject(parent), d(display){}

void Display::powerOn(){
    d->setText("Powering On\n");
    QTimer::singleShot(2000,this,&Display::electrodesCheck);
    QTimer::singleShot(4000,this,&Display::batteriesCheck);
    QTimer::singleShot(5000,this,&Display::responsivenesCheck);
    QTimer::singleShot(8000,this,&Display::call911);
    QTimer::singleShot(11000,this,&Display::placePad);
}
void Display::electrodesCheck(){
    d->setText("Electrodes Are Correctly Placed\n");
}
void Display::batteriesCheck(){
    d->setText("Batteries are installed");
}


void Display::powerOff(){
    d->setText("Powering Off\n");
}


void Display::replaceB(){
    d->setText("Batteries need to be replaced");
}


void Display::responsivenesCheck(){
    d->clear();
    d->setText("Checking for responsiveness...");
}

void Display::call911(){
    d->clear();
    d->setText("Calling 911...");
}

void Display::placePad(){
    d->clear();
    d->setText("Please place the correct pad");
}
