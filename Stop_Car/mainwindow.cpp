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

//让小车可以在图像界面显示行走的过程
void MainWindow::mysleep(unsigned int msec)
{
    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);

}

//添加小车
QLabel* MainWindow::Car(float num, QLabel *car)
{
    QMatrix matrix;
    QPixmap pixmap(":/new/prefix1/picture/zuo.png");  //打开一张图片，""中是文件路径
    matrix.rotate(num);  //旋转小车，num旋传度数
    car->setPixmap(pixmap.transformed(matrix, Qt::SmoothTransformation));  //将打开图片放在对应的Label控件上
    return car;
}

//小车行驶到入口
void MainWindow::CarEnter()
{
    //显示小车
    ui->car_1 = Car(0, ui->car_1);

    //获取入口中间位置
    int enter_mid = (ui->enterleft->x() + ui->enterright->x()) / 2 ;

    //小车行驶到入口中间位置
    for(int i = ui->car_1->x(); i > enter_mid; i--){
        ui->car_1->setGeometry(i,ui->car_1->y(),
                             ui->car_1->width(),
                             ui->car_1->height()
                             );
        mysleep(10);
    }

    ui->car_1->clear();   //清除car_1内容
}

//小车驶进小区
void MainWindow::CarVillage()
{
    //获取旋传后的小车
    ui->car_2 = Car(-90, ui->car_2);

    //行驶，进入小区
    for(int i = ui->car_2->y(); i <= ui->village_line->y(); i++){
        ui->car_2->setGeometry(ui->car_2->x(),i,
                             ui->car_2->width(),
                             ui->car_2->height()
                             );
        mysleep(10);
    }

    ui->car_2->clear();  //清除car_2内容
}

//小车驶进停车位
void MainWindow::CarParking()
{
    //获取旋传后的小车
    ui->car_3 = Car(0, ui->car_3);

    //车位A1的中间位置
    int A1_mid = (ui->A1->x() * 2 + ui->A1->width()) / 2;

    //行驶到车位入口
    for(int i = ui->car_3->x(); i > A1_mid; i--){
        ui->car_3->setGeometry(i,ui->car_3->y(),
                             ui->car_3->width(),
                             ui->car_3->height()
                             );
        mysleep(10);
    }

    ui->car_3->clear();  //清除car_3内容

    //获取旋传后的小车
    ui->car_4 = Car(-90, ui->car_4);

    //驶进停车位A1
    for(int i = ui->car_4->y(); i < ui->A1->y()+10; i++){
        ui->car_4->setGeometry(ui->car_4->x(),i,
                             ui->car_4->width(),
                             ui->car_4->height()
                             );
        mysleep(10);
    }
}

void MainWindow::run()
{
    //小车行驶到入口
    CarEnter();
    //小车进入小区
    CarVillage();
    //小车行驶到车位
    CarParking();
}
