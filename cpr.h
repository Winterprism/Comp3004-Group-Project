#ifndef CPR_H
#define CPR_H

#include <QObject>
#include <QTextEdit>
#include <QElapsedTimer>


class CPR:public QObject
{
    Q_OBJECT
public:
    explicit CPR(QTextEdit *display, QObject *parent = nullptr);
    void trackPresses();
    void analyzeInterval();

private:
    QTextEdit *d;
    QElapsedTimer *timer;
    int counter=0;
};

#endif // CPR_H
