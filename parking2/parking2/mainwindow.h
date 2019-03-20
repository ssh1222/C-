#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QApplication>
#include <QDebug>
#include <string>
#include <qfile.h>
#include <qtextstream.h>
#include <iostream>
#include <QDateTime>
#include<fstream>
#include<map>
#define CHECK_LENGTH 5
#define INSTANCE 3

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
public:
    void run();
    void mysleep(unsigned int msec);
    void parking();
    void FencesPower(int car_x,int car_y);  //栅栏控制
    void redEnterCheck(int car_x,int car_y);//红外检测入口栅栏何时关闭
    void FencesEnterOn();                   //入口栅栏开
    void FencesEnterOff();                  //入口栅栏关
    void FencesExitOn();                    //出口栅栏开
    void FencesExitOff();                   //出口栅栏关
    void setCarInfo(QString carName,QString money,QString brand);//设置小车信息
    void stopCarTime(unsigned int msec);    //停车时间
    void scanCar();                         //扫描仪扫描小车信息
    void writeTofile(QString carInfo);      //将小车信息写入文件函数
    void splitCarInfor(QString carInfo,vector<string>& v);  //切割小车信息
    QString readFromFile(QString path);     //返回从数据库中获取到的车位信息
    void showToEnter(QString carInfo);      //入口显示屏显示小车信息
    void getSysTime();                      //获取系统当前时间
    string readSqlCar();                    //读取小车的车位信息
    int judgeIsNullOfCar(QString linestr);  //判断从数据库中获取到的车位是否被占用
    void splitCarPort(string& str);
    void setParkFlag();                     //更改小车标志位
    void writeDataFile(int count);
    void initCarPort();                     //map中初始化车位和标志位
    string judgeCarPortFlag();              //判断车位标志能否停车
    bool readPositionFromFile(QString path);//从文件中读指定车位的位置信息
    bool isPort(string lineStr);            //判断从文件中读到的信息与对应车位是否一致
    void exitPark();                        //驶出停车场
    void scanCarExit();                     //出口扫描仪扫描小车信息
private:
    void getXY(string lineStr);             //提取lineStr的xy设置mx,my
    string setWork();
    void cheatPark();                       //诱导停车
    void wheel();                           //车辆转弯
    void stopPark();                        //车位停车
    void walkExit();
    void walkFangxiangToExit();
private:
    Ui::MainWindow *ui;
    map<string,int> maplive;                 //车位，标志
    string mCarPort;                         //车位
    int mx;                                  //车位x坐标
    int my;                                  //车位y坐标
    string mLocalTime;

};

#endif // MAINWINDOW_H
