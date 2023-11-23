#ifndef CPR_H
#define CPR_H


class CPR
{
public:
    CPR();
    void enableCPR();
    bool isCPREnabled();

private:
    bool enabled;
};

#endif // CPR_H
