#include "cpr.h"

CPR::CPR()
{
    this->enabled = false;
    this->isPerforming = false;
}

void CPR::enable()
{
    this->enabled = true;
}

bool CPR::isEnabled(){
    return this->enabled;
}

void CPR::perform(){
    this->isPerforming = true;
}

void CPR::stop(){
    this->isPerforming = false;
}
