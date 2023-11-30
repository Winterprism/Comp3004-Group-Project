#ifndef HEARTRATEMONITOR_H
#define HEARTRATEMONITOR_H

#include <QObject>
#include <QSlider>
#include <QTextEdit>
#include <QTimer>
#include <random>


class HeartRateMonitor : public QObject
{
    Q_OBJECT

public:
    HeartRateMonitor(QSlider *slider, QTextEdit *heartRateDisplay, QObject *parent = nullptr);
    void stopOrStartMonitoring();

private slots:
    void updateHeartRate();

private:
    QSlider *slider;
    QTextEdit *heartRateDisplay;
    QTimer *timer;
    std::mt19937 gen; // Random number generator
    int currentAverageRate;

    int generateHeartRate();
};

#endif // HEARTRATEMONITOR_H
