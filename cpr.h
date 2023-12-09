#ifndef CPR_H
#define CPR_H
#include <QLCDNumber>
#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QElapsedTimer>
#include <QTimer>
#include "display.h"


class CPR:public QObject
{
    Q_OBJECT
public:
    explicit CPR(QTextEdit *d,QPushButton *cpr,QTextEdit *led,QObject *parent = nullptr);
    void resetCounter();

public slots:
    void trackPresses();
    void lights();
    void updateTimer();
    void resetLight();
signals:
        void countReachedTen();
private:
    QTextEdit *display;
    QPushButton *c;
    QTextEdit *led;
    QTimer *lightTimer;
    QElapsedTimer *timer;
    QElapsedTimer *timer2;
    int counter;
    int i;
    int currentTime;
    int colorIndc = 0;
    QLCDNumber *lcdNumber;
};

#endif // CPR_H
