#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTime>
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
    QString setCarInfo(QString carName,QString brand,QString carPort); //设置小车信息
    string getSysTime();                    //获取系统当前时间
    void splitCarInfor(QString carInfo,vector<string>& v);  //切割小车信息
    void showenterCar(QString carInfo);     //入口获取小车信息
    void FencesEnterOn();                   //红外检测小车位置，打开栅栏
    void FencesEnterOff();                  //红外检测小车位置，关闭栅栏
    void scanCar();                         //入口显示小车信息
    void pullintoPacking();                 //驶进停车场
    void stopCarTime(unsigned int msec);    //停车时间
    void showexitCar(QString carInfo);      //出口获取小车信息
    void FencesExitOn();                    //红外检测小车位置，打开栅栏
    void FencesExitOff();                   //红外检测小车位置，关闭栅栏
    void scanCarExit();                     //出口显示小车信息
    void pulloutPacking();                  //驶出停车场
    void startPosition();                   //回到起始位置
    void run();                             //主函数

private:
    Ui::MainWindow *ui;
    string mLocalTime;                      //系统时间
};

#endif // MAINWINDOW_H
