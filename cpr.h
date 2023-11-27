#ifndef CPR_H
#define CPR_H


class CPR
{
public:
    CPR();
    void enable();
    bool isEnabled();
    void perform();
    void stop();

private:
    bool enabled;
    bool isPerforming;
};

#endif // CPR_H
