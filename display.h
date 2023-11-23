#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>

class Display:public QObject
{
    Q_OBJECT
public:
    explicit Display(QTextEdit *display, QObject *parent = nullptr);
    void batteriesCheck();
    void electrodesCheck();

public slots:
    void powerOn();
    void powerOff();
    void replaceB();
private:
    QTextEdit *d;
};

#endif // DISPLAY_Ha
