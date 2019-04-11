#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTime>
#include <QTimer>
#include <String>
#include <QDateTime>

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
    void run();     //运行函数
    void mysleep(unsigned int msec);        //设置睡眠时间
    QString setCarInfo(QString name,QString money,QString pack); //设置小车信息
    string getSysTime();                    //获取系统当前时间
    void splitCarInfor(QString carInfo,vector<string>& v);  //切割小车信息
    void showenterCar(QString carInfo);     //入口获取小车信息
    void FencesEnterOn();            //打开栅栏
    void FencesEnterOff();           //关闭栅栏
    void enterShowCar();             //入口显示小车信息
    void intoPack();                 //进停车场
    void stopCarTime(unsigned int msec);    //停车时间
    void showexitCar(QString carInfo);      //出口获取小车信息
    void FencesExitOn();                    //打开栅栏
    void FencesExitOff();                   //关闭栅栏
    void exitShowCar();             //出口显示小车信息
    void outPack();                 //出停车场
    void car1Driving();             //小车car1行驶
    void start();                   //回到起始位置

private slots:
    void onLRTimerOut();            //左右红绿灯时间控制
    void onUDTimerOut();            //上下红绿灯时间控制

private:
    Ui::MainWindow *ui;
    string mLocalTime;
    int settimer1, settimer2;   //判断左右红绿灯
    int settimer3, settimer4;   //判断上下红绿灯
    QTimer *timer1;    //控制上下红绿灯时间
    QTimer *timer2;    //控制左右红绿灯时间
};

#endif // MAINWINDOW_H
