#ifndef DISPLAY_H
#define DISPLAY_H

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
    void responsivenesCheck();
    void call911();
    void heartIsStopped();
    void placePad();
    void updateDisplay();
    void stable();
    void startSelfTest();
private:
    bool interrupt;
    QTextEdit *d;
    int currentStep;
    QStringList steps;
    QTimer *timer;
};

#endif // DISPLAY_Ha
