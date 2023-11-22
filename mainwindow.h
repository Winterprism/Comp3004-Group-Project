#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>

#include "cpr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString padChoice;


private:
    Ui::MainWindow *ui;

private slots:
    void placePad();
    void bodyType(int index);
    void shockDelivery();


    void placePadIncorrectly();

};
#endif // MAINWINDOW_H
