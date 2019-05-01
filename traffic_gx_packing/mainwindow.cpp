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
QString MainWindow::setCarInfo(QString name,QString money,QString pack)
{
    QString info = name+" "+money+" "+pack+" ";    //设置小车信息
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
    carInfo = setCarInfo("Benz","1200000","A3");
    splitCarInfor(carInfo,carSpliteInfo);
    vector<string> v;
    v.push_back("name:");  //显示小车名字
    v.push_back("money:");  //显示小车商标
    v.push_back("pack:"); //车位
    v.push_back("time:");  //显示系统时间
    string s;
    int i = 0;
    for(i = 0; i < carSpliteInfo.size(); i++)
    {
        s += v[i]+carSpliteInfo[i]+'\n';  //将小车信息截取出来
    }
    s = s + v[i]+getSysTime();
    ui->enterShow->setText(s.c_str());   //显示小车信息
}

//入口扫描显示的信息
void MainWindow::enterShowCar()
{
    if(ui->car->y() == ui->enterRed->y())  //判断显示信息时间
    {
        QString carInfo = ui->car->text();
        showenterCar(carInfo);
    }
}

//红外检测入口栅栏打开
void MainWindow::FencesEnterOn()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line->x();

    ui->enterline->setGeometry(ui->enterline->x(),
                            ui->enterline->y(),
                            ui->enterline->width()-distanceInEnterDoor,
                            ui->enterline->height());
}

//红外检测入口栅栏关闭
void MainWindow::FencesEnterOff()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line->x();

    ui->enterline->setGeometry(ui->enterline->x(),
                            ui->enterline->y(),
                            ui->enterline->width()+distanceInEnterDoor,
                            ui->enterline->height());
}

//小车驶进停车位
void MainWindow::intoPack()
{
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/you.png");  //获取小车位置
    matrix.rotate(0);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向右行驶
    for(int i = ui->car->x();i < ui->singleLight_4->x()-ui->car->width(); i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //判断是红灯还是绿灯，绿灯走，红的等停止settimer1的时间
    if(settimer1 >= 0)
        mysleep(settimer1 * 1100+200);

    //继续向右行驶
    for(int i = ui->car->x(); i < ui->line_2->x()-ui->car->width() + 30; i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向下行驶
    for(int i = ui->car->y(); i < ui->enterline->y() - ui->car->height(); i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //进入停车场
    for(int i = ui->car->y(); i < ui->enterRed->y() + ui->car->height(); i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(35);
        //打开栅栏
        if(ui->car->y() + ui->car->height() == ui->enterline->y()){
            FencesEnterOn();
        }
        //关闭栅栏
        if(ui->car->y() - 20 == ui->enterline->y()){
            FencesEnterOff();
        }
        if(ui->car->y() == ui->enterRed->y()){
            enterShowCar();
        }
    }

    //显示屏关闭，显示入口信息
    ui->enterShow->clear();
    ui->enterShow->setText("入口显示");

    //加速
    for(int i = ui->car->y(); i < ui->line_7->y() - 45; i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    for(int i = ui->car->x(); i > ui->carPack->x(); i--){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //右转
    matrix.rotate(-90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //倒进停车位
    for(int i = ui->car->y(); i > ui->carPack->y(); i--){
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
    carInfo = setCarInfo("Benz","1200000","A3");
    splitCarInfor(carInfo,carSpliteInfo);
    vector<string> v;
    v.push_back("name:");  //显示小车名字
    v.push_back("money:");  //显示小车商标
    v.push_back("pack:"); //车位
    v.push_back("time:");  //显示系统时间
    string s;
    int i = 0;
    for(i = 0; i < carSpliteInfo.size(); i++)
    {
        s += v[i]+carSpliteInfo[i]+'\n';   //将小车信息截取出来
    }
    s = s + v[i]+getSysTime();
    ui->exitShow->setText(s.c_str());    //显示小车信息
}

//出口扫描显示小车信息
void MainWindow::exitShowCar()
{
    if(ui->car->y() == ui->exitRed->y())   //判断显示信息时间
    {
        QString carInfo = ui->car->text();
        showexitCar(carInfo);
    }
}

//红外检测出口栅栏打开
void MainWindow::FencesExitOn()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line_6->x();

    ui->exitline->setGeometry(ui->exitline->x(),
                            ui->exitline->y(),
                            ui->exitline->width()-distanceInEnterDoor,
                            ui->exitline->height());
}

//红外检测出口栅栏关闭
void MainWindow::FencesExitOff()
{
    int distanceInEnterDoor = ui->line_2->x()-ui->line_6->x();

    ui->exitline->setGeometry(ui->exitline->x(),
                            ui->exitline->y(),
                            ui->exitline->width()+distanceInEnterDoor,
                            ui->exitline->height());
}

//驶出停车场
void MainWindow::outPack()
{
    //驶出停车位
    for(int i = ui->car->y(); i < ui->line_9->y() - 45; i++){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height());
        mysleep(10);
    }

    //左转
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/xia.png");  //获取小车位置
    matrix.rotate(-90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //行驶到出口
    for(int i = ui->car->x(); i < ui->exitRed->x()+25; i++){
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
    for(int i = ui->car->y(); i < ui->car->height()+ui->exitline->y(); i++){
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
        if(ui->car->y() == ui->exitRed->y()){
            exitShowCar();
        }
    }

    //显示屏关闭，显示出口信息
    ui->exitShow->clear();
    ui->exitShow->setText("出口显示");
}

//小车在停车位停止时间
void MainWindow::stopCarTime(unsigned int msec)
{
    mysleep(msec);
}

//小车走到开始位置
void MainWindow::start()
{
    //右转
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/xia.png");  //获取小车位置
    matrix.rotate(90);  //旋转小车
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
    for(int i = ui->car->y(); i > ui->line_11->y(); i--){
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(5);
    }

    //右转
    matrix.rotate(90);  //旋转小车
    ui->car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向右走
    for(int i = ui->car->x(); i < ui->line_11->x() - ui->car->x(); i++){
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(5);
    }
}

//设置左右方向上红黄绿灯显示，小车在红绿灯处的停止时间
void MainWindow::onLRTimerOut(){
   if(settimer1==0)
    {
        ui->yellow_4->show();
        ui->red_4->hide();
        ui->green_4->hide();
        ui->yellow_2->show();
        ui->red_2->hide();
        ui->green_2->hide();
        mysleep(200);

        ui->green_4->show();
        ui->red_4->hide();
        ui->yellow_4->hide();
        ui->green_2->show();
        ui->red_2->hide();
        ui->yellow_2->hide();

        settimer2 = 10;
        settimer1=-1;
        ui->lcdNumber_2->display(settimer2);
        ui->lcdNumber_4->display(settimer2);
    }
    else if(settimer1>0)
    {
        settimer1--;

        ui->red_4->show();
        ui->yellow_4->hide();
        ui->green_4->hide();
        ui->red_2->show();
        ui->yellow_2->hide();
        ui->green_2->hide();
        ui->lcdNumber_2->display(settimer1);
        ui->lcdNumber_4->display(settimer1);
    }

   if(settimer2==0)
   {


       ui->yellow_4->show();
       ui->red_4->hide();
       ui->green_4->hide();
       ui->yellow_2->show();
       ui->red_2->hide();
       ui->green_2->hide();
       mysleep(200);

       ui->red_4->show();
       ui->green_4->hide();
       ui->yellow_4->hide();
       ui->red_2->show();
       ui->green_2->hide();
       ui->yellow_2->hide();

       settimer1 = 10;
       settimer2 = -1;
       ui->lcdNumber_2->display(settimer1);
       ui->lcdNumber_4->display(settimer1);
   }
   else if(settimer2>0)
   {
       settimer2--;
       ui->lcdNumber_2->display(settimer2);
       ui->lcdNumber_4->display(settimer2);
       ui->green_4->show();
       ui->yellow_4->hide();
       ui->red_4->hide();
       ui->green_2->show();
       ui->yellow_2->hide();
       ui->red_2->hide();
   }
}

//小车car1的行驶
void MainWindow::car1Driving(){
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/xia.png");  //获取小车位置
    matrix.rotate(0);  //旋转小车
    ui->car1->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向下走
    for(int i = ui->car1->y(); i < ui->singleLight->y()-ui->car1->height(); i++){
        ui->car1->setGeometry(ui->car1->x(),i,
                             ui->car1->width(),
                             ui->car1->height());
        mysleep(10);
    }

    //判断是否停车
    if(settimer4 >= 0)
        mysleep(settimer4 * 1100+1000);

    //继续往下走
    for(int i = ui->car1->y(); i < ui->singleLight_3->y() - ui->car1->height(); i++){
        ui->car1->setGeometry(ui->car1->x(),i,
                             ui->car1->width(),
                             ui->car1->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car1->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向右行驶
    for(int i = ui->car1->x(); i < ui->enterShow->x()+ui->enterShow->width(); i++){
        ui->car1->setGeometry(i,ui->car1->y(),
                             ui->car1->width(),
                             ui->car1->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car1->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //向上行驶
    for(int i = ui->car1->y(); i > 0; i--){
        ui->car1->setGeometry(ui->car1->x(),i,
                             ui->car1->width(),
                             ui->car1->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car1->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));

    //回到起始位置
    for(int i = ui->car1->x(); i > ui->line_13->x() + 25; i--){
        ui->car1->setGeometry(i,ui->car1->y(),
                             ui->car1->width(),
                             ui->car1->height());
        mysleep(10);
    }

    //左转
    matrix.rotate(-90);  //旋转小车
    ui->car1->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));
}

//设置上下方向上红黄绿灯显示，小车在红绿灯处的停止时间
void MainWindow::onUDTimerOut(){
   if(settimer3==0)
    {
        ui->yellow->show();
        ui->red->hide();
        ui->green->hide();
        ui->yellow_3->show();
        ui->red_3->hide();
        ui->green_3->hide();
        mysleep(200);

        ui->green->hide();
        ui->red->show();
        ui->yellow->hide();
        ui->green_3->hide();
        ui->red_3->show();
        ui->yellow_3->hide();

        settimer4 = 10;
        settimer3=-1;
        ui->lcdNumber->display(settimer4);
        ui->lcdNumber_4->display(settimer4);
    }
    else if(settimer3>0)
    {
        settimer3--;

        ui->red->hide();
        ui->yellow->hide();
        ui->green->show();
        ui->red_3->hide();
        ui->yellow_3->hide();
        ui->green_3->show();
        ui->lcdNumber->display(settimer3);
        ui->lcdNumber_3->display(settimer3);
    }

   if(settimer4==0)
   {


       ui->yellow->show();
       ui->red->hide();
       ui->green->hide();
       ui->yellow_3->show();
       ui->red_3->hide();
       ui->green_3->hide();
       mysleep(200);

       ui->red->hide();
       ui->green->show();
       ui->yellow->hide();
       ui->red_3->hide();
       ui->green_3->show();
       ui->yellow_3->hide();

       settimer3 = 10;
       settimer4 = -1;
       ui->lcdNumber->display(settimer3);
       ui->lcdNumber_3->display(settimer3);
   }
   else if(settimer4>0)
   {
       settimer4--;
       ui->lcdNumber->display(settimer4);
       ui->lcdNumber_3->display(settimer4);
       ui->green->hide();
       ui->yellow->hide();
       ui->red->show();
       ui->green_3->hide();
       ui->yellow_3->hide();
       ui->red_3->show();
   }
}


//主函数
void MainWindow::run()
{
    //左右小车car红绿灯设置
    settimer1 = 10;
    settimer2 = -1;
    ui->yellow_2->hide();
    ui->green_2->hide();
    ui->yellow_4->hide();
    ui->green_4->hide();
    ui->lcdNumber_2->display(settimer1);
    ui->lcdNumber_4->display(settimer1);
    timer1 = new QTimer();
    timer1->setInterval(1000);
    timer1->start();

    connect(timer1,SIGNAL(timeout()),this, SLOT(onLRTimerOut()));

    //上下小车car1/红绿灯的设置
    settimer3 = 10;
    settimer4 = -1;
    ui->yellow->hide();
    ui->red->hide();
    ui->yellow_3->hide();
    ui->red_3->hide();
    ui->lcdNumber->display(settimer3);
    ui->lcdNumber_3->display(settimer3);
    timer2 = new QTimer();
    timer2->setInterval(1000);
    timer2->start();

    connect(timer2,SIGNAL(timeout()),this, SLOT(onUDTimerOut()));

    while(1){
        car1Driving();      //行驶小车car1
        intoPack();         //进停车场
        stopCarTime(1000);  //小车在停车位停止时间
        outPack();          //出停车场
        start();            //回到起始位置
        stopCarTime(1000);  //小车在起始位停止时间
    }
}
