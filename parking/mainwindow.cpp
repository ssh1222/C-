/*author:孙世豪
 *time:2019/3/28
 *function:模拟小车驶入停车场
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置睡眠时间
void MainWindow::mysleep(unsigned int msec)
{
    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);

}

//设置小车文本信息
QString MainWindow::setCarInfo(QString carName,QString brand,QString carPort)
{
    QString info = carName+" "+brand+" "+carPort+" ";    //设置小车信息
    return info;
}

//获取系统时间
string MainWindow::getSysTime()
{
    QDateTime local(QDateTime::currentDateTime());
    mLocalTime = local.toString().toStdString();
    return mLocalTime;
}

//切割小车信息
void MainWindow::splitCarInfor(QString carInfo,vector<string>& v)
{
     string str = carInfo.toStdString();   //获取carInfo中的所有字符串
     while(1)
     {
         int idx = str.find(" ");     //找" "，获取" "所在位置
         if(idx==-1)    //获取失败返回-1，读取完毕，退出
         {
             break;
         }
         string s = str.substr(0,idx);  //获取str中从0位置到idx位置的字符串
         v.push_back(s);   //将字符串写入v所指字符串的尾部
         str = str.substr(idx+1,str.length());  //将idx后面剩余部分重新赋值给str，重新获取字符串中的信息
     }
}

//入口获取小车信息
void MainWindow::showenterCar(QString carInfo)
{
    vector<string> carSpliteInfo;  //小车的信息划分存储
    carInfo = setCarInfo("陕A8888","劳斯莱斯","A6");
    splitCarInfor(carInfo,carSpliteInfo);
    //getSysTime();    //获取系统时间
    vector<string> v;
    v.push_back("carname:");  //显示小车名字
    v.push_back("brand:");  //显示小车商标
    v.push_back("packing:"); //车位
    v.push_back("time:");  //显示系统时间
    string s;
    string sub;
    int i = 0;
    for(i = 0; i < carSpliteInfo.size(); i++)
    {
        sub = v[i]+carSpliteInfo[i]+'\n';  //将小车信息截取出来
        s += sub;
    }
    s = s + v[i]+getSysTime();
    ui->enterLabel->setText(s.c_str());   //显示小车信息
}

//入口扫描显示的信息
void MainWindow::scanCar()
{
    if(ui->car->y() == ui->enter->y())  //判断显示信息时间
    {
        QString carInfo = ui->car->text();
        showenterCar(carInfo);
    }
}

//红外检测入口栅栏打开
void MainWindow::FencesEnterOn()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line->x() + 30;

    ui->enterline->setGeometry(ui->enterline->x(),
                            ui->enterline->y(),
                            ui->enterline->width()-distanceInEnterDoor,
                            ui->enterline->height());
}

//红外检测入口栅栏关闭
void MainWindow::FencesEnterOff()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line->x() + 30;

    ui->enterline->setGeometry(ui->enterline->x(),
                            ui->enterline->y(),
                            ui->enterline->width()+distanceInEnterDoor,
                            ui->enterline->height());
}

//小车驶进停车位
void MainWindow::pullintoPacking()
{
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/you.png");  //获取小车位置
    matrix.rotate(0);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向右行驶
    for(int i = ui->car->x(); i < (ui->enter->x()*2 + ui->enter->width()/2)/2; i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //右转
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //驶进停车位
    for(int i = ui->car->y(); i < ui->line_7->y()-ui->car->height() - 10; i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(35);
        //打开栅栏
        if(ui->car->y()+ui->car->height() == ui->enterline->y()){
            FencesEnterOn();
        }
        //关闭栅栏
        if(ui->car->y() - 10 == ui->enterline->y()){
            FencesEnterOff();
        }
        scanCar();
    }

    //显示屏关闭，显示入口信息
    ui->enterLabel->clear();
    ui->enterLabel->setText("入口显示");

    //加速
    for(int i = ui->car->y(); i < ui->line_4->y()-ui->car->height() + 15; i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    for(int i = ui->car->x(); i < (ui->line_17->x()+ui->line_18->x())/2 - 10; i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //倒进停车位
    for(int i = ui->car->y(); i < ui->spot->y(); i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(40);
    }
}

//出口获取小车信息
void MainWindow::showexitCar(QString carInfo)
{
    vector<string> carSpliteInfo;  //小车的信息划分存储
    carInfo = setCarInfo("陕A8888","劳斯莱斯","A6");
    splitCarInfor(carInfo,carSpliteInfo);
    //getSysTime();    //获取系统时间
    vector<string> v;
    v.push_back("carname:");  //显示小车名字
    v.push_back("brand:");  //显示小车商标
    v.push_back("packing:"); //车位
    v.push_back("time:");  //显示系统时间
    string s;
    string sub;
    for(int i = 0; i < carSpliteInfo.size(); i++)
    {
        sub = v[i]+carSpliteInfo[i]+'\n';   //将小车信息截取出来
        s += sub;
    }
    s = s + v[3]+getSysTime();
    ui->exitLabel->setText(s.c_str());    //显示小车信息
}

//出口扫描显示小车信息
void MainWindow::scanCarExit()
{
    if(ui->car->y() == ui->exit->y())   //判断显示信息时间
    {
        QString carInfo = ui->car->text();
        showexitCar(carInfo);
    }
}

//红外检测出口栅栏打开
void MainWindow::FencesExitOn()
{
    int distanceInEnterDoor = ui->line_6->x()-ui->line_5->x();

    ui->exitline->setGeometry(ui->exitline->x(),
                            ui->exitline->y(),
                            ui->exitline->width(),
                            ui->exitline->height()-distanceInEnterDoor);
}

//红外检测出口栅栏关闭
void MainWindow::FencesExitOff()
{
    int distanceInEnterDoor = ui->line_6->x()-ui->line_5->x();

    ui->exitline->setGeometry(ui->exitline->x(),
                            ui->exitline->y(),
                            ui->exitline->width(),
                            ui->exitline->height()+distanceInEnterDoor);
}

//驶出停车场
void MainWindow::pulloutPacking()
{
    //驶出停车位
    for(int i = ui->car->y(); i > ui->line_7->y(); i--){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(10);
    }

    //右转
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/you.png");  //获取小车位置
    matrix.rotate(0);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //行驶到出口
    for(int i = ui->car->x(); i < (ui->exit->x()*2 + 20)/2; i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //右转
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //减速
    for(int i = ui->car->y(); i < ui->car->height()+ui->exit->y(); i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(30);
        //打开栅栏
        if(ui->car->y()+ui->car->height() == ui->exitline->y()){
            FencesExitOn();
        }
        //关闭栅栏
        if(ui->car->y() - 10 == ui->exitline->y()){
            FencesExitOff();
        }
        scanCarExit();
    }

    //显示屏关闭，显示出口信息
    ui->exitLabel->clear();
    ui->exitLabel->setText("出口显示");
}

//小车在停车位停止时间
void MainWindow::stopCarTime(unsigned int msec)
{
    mysleep(msec);
}

//小车走到开始位置
void MainWindow::startPosition()
{
    //右转
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/you.png");  //获取小车位置
    matrix.rotate(180);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向左走
    for(int i = ui->car->x(); i > 0; i--){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(5);
    }

    //右转
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向上走
    for(int i = ui->car->y(); i > 0; i--){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(5);
    }

    //右转，回到起始位置
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));
}

//主函数
void MainWindow::run()
{
    while(1){
        pullintoPacking();  //驶进停车场
        stopCarTime(2000);  //小车在停车位停止时间
        pulloutPacking();   //驶出停车场
        startPosition();    //回到起始位置
        stopCarTime(2000);  //小车在起始位停止时间
    }
}
