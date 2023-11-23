#include "cpr.h"

CPR::CPR()
{
    this->enabled = false;
}

void CPR::enableCPR()
{
    this->enabled = true;
}

bool CPR::isCPREnabled(){
    return this->enabled;
}
