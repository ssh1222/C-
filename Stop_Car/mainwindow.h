#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QTime>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void run();
    void mysleep(unsigned int msec);
    QLabel* Car(float num, QLabel *car);   //设置小车，让小车旋传
    void CarEnter();  //小车行驶到入口位置
    void CarVillage();  //小车驶进小区
    void CarParking();  //小车驶进停车位

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
