#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <random>
#include "display.h"
#include "cpr.h"
#include "HeartRateMonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void powerOn();
    void powerOff();
    void replaceB();
    int getIndcColor();
    void call911();
    void heartIsStopped();
    void stable();
    void checkRes();
    void placeP();

private:
    QString padChoice;
    bool powerIsOn = false;
    Ui::MainWindow *ui;
    QLabel *processLabel;
    QMovie *movie;
    QTimer *heartRateTimer;
    QTimer *drainTimer;
    bool mouthToMouthReady;
    HeartRateMonitor *heartRateMonitor;
    int cprClickedCounter = 0;
//    void alternateCPRIndc();
//    void receiveCPRIndc();
    bool shockPerformed = false;
private slots:
    void placePad();
    void bodyType(int index);
    void shockDelivery();
    void power();
    void replaceBattery();
    void drainBattery();
    void placePadIncorrectly();
    void patientContactDuringShockDelivery();
    void checkForMouthToMouthPress();
    void performMouthtoMouth();
    void shockTimer();
    void shockTimerDelay();
    void disableAllButtons();
    void enableAllButtons();
    void AEDInitialLightUp();
    void lightUpDelay(int);
    void startUpLights();
    void patientHeartStopped();
    void shockAdvised();
    void heartRateChanger();
    void padsLossConnection();

};
#endif // MAINWINDOW_H
