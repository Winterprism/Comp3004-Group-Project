#include "cpr.h"

CPR::CPR(QTextEdit *display, QObject *parent):QObject(parent), d(display)
{
    this->timer = new QElapsedTimer();
}

/* Button press interval:
 * - intervals always last 3 seconds
 * - >=5 presses in 3 seconds is too fast, display will indicate to slow down (red light will flash)
 * - 1 press in 3 seconds is too slow, display indicates
*/

void CPR::trackPresses(){
    if (counter == 0) {
        timer->start();
    }

    d->clear();
    d->append("CPR pressed " + QString::number(counter+1) + " times in last " +
              QString::number(timer->elapsed() / 1000) + " seconds\n");

    if (!timer->hasExpired(9300)) {
        counter++;
    }else{
        this->analyzeInterval();
        counter = 0;
    }
}

void CPR::analyzeInterval(){
    //Assuming the interval is 10 seconds

    // when pressing speed is too fast (>=5)
    if (counter > 15) {
        d->append("Slow down!\n");
        colorIndc = 1;
        getIndcColor(); //red
    } //when pressing speed is too slow (<=1)
    else if (counter < 5){
        d->append("Press faster\n");
        colorIndc = 1;
        getIndcColor(); //red
    } //when pressing speed is just right
    else{
        d->append("CPR performing well\n");
        colorIndc = 2;
        getIndcColor(); //green
    }
}

int CPR::getIndcColor(){
    return colorIndc;
}

void CPR::resetCounter(){
    counter = 0;
}
