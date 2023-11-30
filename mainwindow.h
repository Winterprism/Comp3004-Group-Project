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

    QString padChoice;
signals:
    void powerOn();
    void powerOff();
    void replaceB();

private:
    Ui::MainWindow *ui;
    QLabel *processLabel;
    QMovie *movie;
    QTimer *drainTimer;
    bool mouthToMouthReady;
    HeartRateMonitor *heartRateMonitor;

private slots:
    void placePad();
    void bodyType(int index);
    void shockDelivery();
    void power();
    void replaceBattery();
    void drainBattery();
    void placePadIncorrectly();
    void patientContactDuringShockDelivery();
    void cprPressed();
    void checkForMouthToMouthPress();
    void performMouthtoMouth();

};
#endif // MAINWINDOW_H
