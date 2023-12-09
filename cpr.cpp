#include "cpr.h"

CPR::CPR(QTextEdit *d,QPushButton *cpr ,QTextEdit *led,QObject *parent):QObject(parent), display(d),c(cpr), led(led),currentTime(0),counter(0),i(0)
{
    connect(c, SIGNAL(released()), this, SLOT(trackPresses()));
    timer = new QElapsedTimer();
    timer2 = new QElapsedTimer();
    lightTimer = new QTimer(this);
    lightTimer->setInterval(1000);
    connect(lightTimer, &QTimer::timeout, this, &CPR::lights);
}

/* Button press interval:
 * - intervals always last 3 seconds
 * - >=5 presses in 3 seconds is too fast, display will indicate to slow down (red light will flash)
 * - 1 press in 3 seconds is too slow, display indicates
*/

void CPR::trackPresses(){
    lightTimer->start();
    led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(220, 20, 60)");
    display->clear();
    display->append("CPR pressed " + QString::number(counter) + " times\n");
    if (counter == 0) {
        timer->start();
        lightTimer->start(1000);
    }
    counter++;
    i++;
    if (timer->elapsed() >= 3000) {
        if(i < 2){
            display->append("Press faster\n");
        }
        else if (i >= 5) {
               display->append("Slow down!\n");
        }else{

            display->append("CPR performing well\n");
        }
        i = 0;
        timer->restart();

    }if(counter == 11){
        emit countReachedTen();
        counter = 0;
        timer->restart();
        lightTimer->stop();
        led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;");

    }
}

void CPR::lights(){
     led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(51, 209, 122)");
//    if(colorIndc  == 1){
//        led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(51, 209, 122)");
//        colorIndc--;
//    }
//    else if(colorIndc  == 0){
//        led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(220, 20, 60)");
//        colorIndc++;
//    }

}

void CPR::resetLight() {
     led->setStyleSheet("color: #333;border: 2px solid #555;border-radius: 20px;border-style: outset;background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);padding: 5px;background-color: rgb(51, 209, 122)");
}

void CPR:: updateTimer(){
    currentTime++;
    lcdNumber->display(currentTime);
}
