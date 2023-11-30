#include "HeartRateMonitor.h"

HeartRateMonitor::HeartRateMonitor(QSlider *slider, QTextEdit *heartRateDisplay, QObject *parent)
    : QObject(parent), slider(slider), heartRateDisplay(heartRateDisplay), gen(std::random_device{}())
{
    currentAverageRate = this->slider->value();


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HeartRateMonitor::updateHeartRate);


    connect(this->slider, &QSlider::valueChanged, this, [=](int value) {
        currentAverageRate = value;
    });
}

void HeartRateMonitor::updateHeartRate()
{
    int heartRate = generateHeartRate();
    heartRateDisplay->setText(QString::number(heartRate));
}

int HeartRateMonitor::generateHeartRate()
{
    std::uniform_int_distribution<> distrib(currentAverageRate - 5, currentAverageRate + 5);
    return distrib(gen);
}
void HeartRateMonitor::stopOrStartMonitoring() {
    if (timer->isActive()) {
        timer->stop();
    }else{
            timer->start(1000);
    }
}
