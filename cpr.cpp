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
        d->setText("Performing CPR");
    }

    if (!timer->hasExpired(10000)) {
        counter++;
    }else{
        this->analyzeInterval();
    }
}

void CPR::analyzeInterval(){
    //Assuming the interval is 10 seconds

    // when pressing speed is too fast (>=5)
    if (counter > 15) {
        d->setText("Slow down!");
    } //when pressing speed is too slow (<=1)
    else if (counter < 5){
        d->setText("Press faster");
        // set led_indicator to red
    } //when pressing speed is just right
    else{
        d->setText("CPR performing well");
        // set led_indicator to green
    }
    counter = 0;
}
