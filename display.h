#ifndef DISPLAY_H
#define DISPLAY_H
#include "mainwindow.h"
#include <QObject>
#include <QTextEdit>
#include <QTimer>

class Display:public QObject
{
    Q_OBJECT
public:
    explicit Display(QTextEdit *display, QObject *parent = nullptr);
    void batteriesCheck();
    void electrodesCheck();

public slots:
    void powerOn();
    void powerOff();
    void replaceB();
    void call911();
    void heartIsStopped();
    void checkRes();
    void placeP();
    void updateDisplay();
    void stable();
private:
    bool interrupt;
    QTextEdit *d;
    int currentStep;
    QStringList steps;
    QTimer *timer;
};

#endif // DISPLAY_Ha
