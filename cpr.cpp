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

    if (!timer->hasExpired(9000)) {
        counter++;
        d->clear();
        d->append("CPR pressed " + QString::number(counter) + " times\n");
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
