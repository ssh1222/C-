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
    void mysleep(unsigned int msec);  //设置睡眠时间
    QString setCarInfo(QString carName,QString brand,QString carPort,QString money); //设置小车信息
    string getSysTime();                    //获取系统当前时间
    void splitCarInfor(QString carInfo,vector<string>& v);  //切割小车信息
    void showenterCar(QString carInfo);     //入口获取小车信息
    void FencesEnterOn();                   //红外检测小车位置，打开栅栏
    void FencesEnterOff();                  //红外检测小车位置，关闭栅栏
    void scanCar();                         //入口显示小车信息
    void stop();                            //设置小车停止
    void pullintoPacking();                 //驶进停车场
    void stopCarTime(unsigned int msec);    //停车时间
    void showexitCar(QString carInfo);      //出口获取小车信息
    void FencesExitOn();                    //红外检测小车位置，打开栅栏
    void FencesExitOff();                   //红外检测小车位置，关闭栅栏
    void scanCarExit();                     //出口显示小车信息
    void pulloutPacking();                  //驶出停车场
    void startPosition();                   //回到起始位置
    void Car1();                            //小车1的行驶路线
    void run();                             //主函数

private slots:
    void onLRTimerOut();                    //设置左右方向上红黄绿灯显示，小车在红绿灯处的停止时间
    void onUDTimerOut();                    //设置上下方向上红黄绿灯显示，小车在红绿灯处的停止时间
private:
    Ui::MainWindow *ui;
    int settime1, settime2;                 //左右红绿灯
    int settime3, settime4;                 //上下红绿灯
    string mLocalTime;                      //系统时间
    QTimer *timer1,*timer2;
};

#endif // MAINWINDOW_H
