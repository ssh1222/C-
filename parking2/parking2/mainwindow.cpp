#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initCarPort()
{
    maplive.insert(pair<string,int>("A1",1));
    maplive.insert(pair<string,int>("A2",1));
    maplive.insert(pair<string,int>("A3",1));
    maplive.insert(pair<string,int>("A4",1));
    maplive.insert(pair<string,int>("A5",1));
    maplive.insert(pair<string,int>("A6",1));
    maplive.insert(pair<string,int>("A7",0));
    maplive.insert(pair<string,int>("A8",0));
    maplive.insert(pair<string,int>("A9",0));
    maplive.insert(pair<string,int>("A10",1));
    maplive.insert(pair<string,int>("A11",1));
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initCarPort();
    mx = my = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mysleep(unsigned int msec)
{
    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);

}

//设置小车文本信息
void MainWindow::setCarInfo(QString carName,QString money,QString brand)
{
    QString info = carName+" "+money+" "+brand+" ";
    ui->car->setText(info);
}

//将小车信息写入文件
void MainWindow::writeTofile(QString carInfo)
{
    QFile f("E:\\qt_work\\parking2\\text.txt");
    if(!f.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        qDebug()<<"Open failed.";
    }else
    {
        QTextStream txtOutput(&f);
        txtOutput<<carInfo<<endl;
    }
    f.close();
}

//获取系统当前时间
/*void MainWindow::getSysTime()
{
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString();

    QDate d = local.date();

    cout<<d.year()<<endl;
    cout<<d.month()<<endl;
    cout<<d.day()<<endl;

    QTime t = local.time();
    cout<<t.hour()<<endl;
    cout<<t.minute()<<endl;
    cout<<t.second()<<endl;
}*/


/*
读文件操作
void MainWindow::readFromFile()
{
    QFile f("F:\\text.txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open failed.";
    }else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            qDebug()<<lineStr;
        }
    }
    f.close();
}
*/

//判断从数据库中获取到的车位判断是否被占用
/*int MainWindow::judgeIsNullOfCar(QString linestr)
{
    string s = linestr.toStdString();
    int flagCar = s[s.length()-1]-'0';
    if(0 == flagCar) return 1;  //说明此车位未被占用
    else return -1;             //说明此车位已被占用
}
//返回从数据库中获取到的车位信息
QString MainWindow::readFromFile(QString path)
{
    QFile f(path);
    QString str = "fill";
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"Open failed.";
    else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            if( judgeIsNullOfCar(lineStr) == 1 )
            {
                f.close();
                str = lineStr;
                break;
            }
        }
    }
    f.close();
    return str;
}*/


//切割小车信息
void MainWindow::splitCarInfor(QString carInfo,vector<string>& v)
{
     string str = carInfo.toStdString();
     while(1)
     {
         int idx = str.find(" ");
         if(idx==-1)
         {
             break;
         }
         string s = str.substr(0,idx);
         v.push_back(s);
         str = str.substr(idx+1,str.length());
     }
}

//切割车位信息
/*void MainWindow::splitCarPort(string& str)
{
    vector<string> v;
    while(1)
    {
        int idx = str.find(" ");
        if(idx==-1)
        {
            break;
        }
        string s = str.substr(0,idx);
        v.push_back(s);
        str = str.substr(idx+1,str.length());
    }
    mCarPort = v[0];
    mx = atoi(v[1].c_str());
    my = atoi(v[2].c_str());
}
//读小车车位信息
string MainWindow::readSqlCar()
{

    QString result = readFromFile("F:\\data.txt");
    return result.toStdString();
}*/


//返回true说明匹配成功
bool MainWindow::isPort(string lineStr)
{
    int len = mCarPort.length();
    int res = -1;
    cout<<"macr:"<<mCarPort<<endl;
    cout<<"str:"<<lineStr<<endl;
    res = lineStr.compare(0,len,mCarPort,0,len);//返回0车位匹配，否则不匹配
    if(res == 0)return true;
    return  false;
}
void MainWindow::getSysTime()
{
    QDateTime local(QDateTime::currentDateTime());
    mLocalTime = local.toString().toStdString();

   /* QDate d = local.date();

    cout<<d.year()<<endl;
    cout<<d.month()<<endl;
    cout<<d.day()<<endl;

    QTime t = local.time();
    cout<<t.hour()<<endl;
    cout<<t.minute()<<endl;
    cout<<t.second()<<endl;*/
}

//设置xy坐标
void MainWindow::getXY(string lineStr)
{
    string str;
    string s;
    //cout<<"lineStr:"<<lineStr<<endl;
    int index = lineStr.find(" ");
    if(index != -1) str = lineStr.substr(index+1,lineStr.length());

    int idx = str.find(" ");
    if(idx != -1)
    {
      mx = atoi( str.substr(0,idx).c_str() );
      my = atoi( str.substr(idx+1,str.length()).c_str() );
    }
}
//从文件中读取对应车位的位置
bool MainWindow::readPositionFromFile(QString path)
{
    QFile f(path);
    bool res = false;
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"Open failed.";
    else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            //cout<<"lineStr:"<<lineStr.toStdString()<<endl;
            res = isPort(lineStr.toStdString());//对比车位是否一致
            //cout<<"res"<<res<<endl;
            if(res)
            { 
                getXY(lineStr.toStdString());//提取并设置xy
                break;
            }
        }
    }
    f.close();
    return res;
}
//判断map中小车的标志位是否被占用，并设置mCarPort满返回fill
string MainWindow::judgeCarPortFlag()
{
    map<string,int>::iterator ite;
    string res = "fill";
    for(ite = maplive.begin();ite != maplive.end();++ite)
    {
        if(ite->second == 0)
        {
            ite->second = 1;
            mCarPort = ite->first;
            return ite->first;
        }
    }
    return res;
}

string MainWindow::setWork()
{
    string res = judgeCarPortFlag();

    if(res.compare("fill") == 0)return res;

    if( readPositionFromFile("E:\\qt_work\\parking2\\data.txt") )
    {
        return res;
    }
}

//入口显示，分配停车位,未满则显示车位，满了则无法停车。。。。
void MainWindow::showToEnter(QString carInfo)
{
    vector<string> carSpliteInfo;  //小车的信息划分存储
    splitCarInfor(carInfo,carSpliteInfo);
    getSysTime();
    vector<string> v;
    v.push_back("card:");
    v.push_back("money:");
    v.push_back("brand:");
    v.push_back("carPort:");
    v.push_back("time:");
    string s;                        //////////////////////////////////
    string sub;
    string str = setWork();  //失败返回fill,成功返回车位

    if(str.compare("fill") == 0) carSpliteInfo.push_back("fill");
    else
    {
       //splitCarPort(str);

       carSpliteInfo.push_back(mCarPort);      //将划分得到的车位加入
       carSpliteInfo.push_back(mLocalTime);
    }

    for(int i=0;i<carSpliteInfo.size();++i)
    {
        cout<<carSpliteInfo[i]<<"   ";
        sub = v[i]+carSpliteInfo[i]+'\n';
        s += sub;
    }
    ui->enterShowLabel->setText(s.c_str());
}



//入口扫描车的信息
void MainWindow::scanCar()
{
    if(ui->car->y() == ui->scanBtn->y())
    {
        QString carInfo = ui->car->text();
        showToEnter(carInfo);
    }
}

//出口扫描仪扫描获取小车信息
void MainWindow::scanCarExit()
{
    if(ui->car->y()+ui->car->height() == ui->exitRed->y())
    {
        QString carInfo = ui->car->text();
        //showToEnter(carInfo);
    }
    FencesExitOn();
}


//红外检测入口栅栏打开
void MainWindow::FencesEnterOn()
{
    int distanceInEnterDoor = ui->enterDoorTwo->x()-ui->enterDoorOne->x();

    ui->fencesEnter->setGeometry(ui->fencesEnter->x(),
                            ui->fencesEnter->y(),
                            ui->fencesEnter->width()-distanceInEnterDoor,
                            ui->fencesEnter->height());
}

//红外检测入口栅栏关闭
void MainWindow::FencesEnterOff()
{
    int distanceInEnterDoor = ui->enterDoorTwo->x()-ui->enterDoorOne->x();

    ui->fencesEnter->setGeometry(ui->fencesEnter->x(),
                            ui->fencesEnter->y(),
                            ui->fencesEnter->width()+distanceInEnterDoor,
                            ui->fencesEnter->height());
}

//红外检测出口栅栏打开
void MainWindow::FencesExitOn()
{
    int distanceInExitDoor = ui->exitDoorTwo->x()-ui->exitDoorOne->x();

    ui->fencesExit->setGeometry(ui->fencesExit->x(),
                             ui->fencesExit->y(),
                             ui->fencesExit->width()-distanceInExitDoor,
                             ui->fencesExit->height());
}
//红外检测出口栅栏关闭
void MainWindow::FencesExitOff()
{
    int distanceInExitDoor = ui->exitDoorTwo->x()-ui->exitDoorOne->x();

    ui->fencesExit->setGeometry(ui->fencesExit->x(),
                             ui->fencesExit->y(),
                             ui->fencesExit->width()+distanceInExitDoor,
                             ui->fencesExit->height());

}



//检测入口栅栏何时打开
void MainWindow::FencesPower(int car_x,int car_y)
{
    int fences_y = ui->fencesEnter->y();
    int car_h = ui->car->height();

    for(int i=car_y; i+car_h<fences_y-CHECK_LENGTH; ++i)
    {
        ui->car->setGeometry(car_x,i,
                             ui->car->width(),
                             ui->car->height());
       mysleep(100);
    }
    FencesEnterOn();
}


//红外检测入口栅栏何时关闭
void MainWindow::redEnterCheck(int car_x,int car_y)
{
    if(car_y == ui->enterRed->y())
        FencesEnterOff();
}


/*void MainWindow::setParkFlag()
{
    maplive.find(mCarPort);
    //fstream file("test.txt",ios::in|ios::out);
    string buff;
    ifstream infile;//=new ifstream(file);
    infile.open("F:\\data.txt",ios::in|ios::out);
    int offset=0;
    int index=-1;
    int count=0;
    while(getline(infile,buff))
    {
        cout<<"count:"<<count<<endl;
        index=buff.find_first_of(" ",offset);

            string str=buff.substr(offset,index-offset);
            count+=buff.length()+1;
            cout<<"length :"<<buff.length();
            cout<<"str:"<<str<<endl;
            if(str==mCarPort)
            {
                //count-=1;
                cout<<"count:"<<count<<endl;
                writeDataFile(count);//she zhi sign;
                break;
            }
    }
}*/

//车位停车时间
void MainWindow::stopCarTime(unsigned int msec)
{
    mysleep(msec);
}

//转弯
void MainWindow::wheel()
{
    if(ui->car->x() > mx)
    {
        for(int i=ui->car->x(); i>mx-INSTANCE; --i)
        {
            ui->car->setGeometry(i,ui->car->y(),
                                 ui->car->width(),
                                 ui->car->height()
                                );
            mysleep(10);
        }
    }else
    {
        for(int i=ui->car->x(); i<mx-INSTANCE; ++i)
        {
            ui->car->setGeometry(i,ui->car->y(),
                                 ui->car->width(),
                                 ui->car->height()
                                );
            mysleep(10);
        }
     }
}
//停车
void MainWindow::stopPark()
{
    if(ui->car->y() > my)
    {
        for(int i=ui->car->y(); i>my+CHECK_LENGTH; --i)
        {
            ui->car->setGeometry(ui->car->x(),i,
                                 ui->car->width(),
                                 ui->car->height()
                                 );
            mysleep(10);
        }
    }else
    {
        for(int i=ui->car->y(); i<my-CHECK_LENGTH; ++i)
        {
            ui->car->setGeometry(ui->car->x(),i,
                                 ui->car->width(),
                                 ui->car->height()
                                 );
            mysleep(10);
        }
    }
}


//诱导停车主函数
void MainWindow::cheatPark()
{
   wheel();
   stopPark();
}
void MainWindow::run()
{
   // getSysTime();
    setCarInfo("a123","50","aodi");
    int car_x = ui->car->x();
    int car_y = ui->car->y();
    FencesPower(car_x,car_y);

    int car_tail_y = ui->car->y()+ui->car->height();
    //直行
    for(int i=ui->car->y(); i+ui->car->height()< ui->downStreet->y(); ++i)
    {
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
        scanCar();
        redEnterCheck(ui->car->x(),i);
        mysleep(100);
    }
    /////////////////////////////////
    /////////////////////////////////
    cheatPark();            //诱导停车
    //转弯
  /*  for(int i=ui->car->x(); i>ui->flagLineFour->x()-INSTANCE; --i)
    {
        ui->car->setGeometry(i,ui->car->y(),
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }

    //停车ui->car->y();i>ui->parkFr->y();--i)

    for(int i=ui->car->y(); i>ui->parkFour->y(); --i)
    {
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
        mysleep(10);
    }*/
    stopCarTime(10); //停车时间    mysleep(1000);
    exitPark();      //出停车场
}

//驶出停车场
void MainWindow::walkExit()
{
    for(int i = ui->car->y();i<ui->scanBtnExit->y();++i)
    {
        ui->car->setGeometry(ui->car->x(),i,
                             ui->car->width(),
                             ui->car->height()
                             );
            mysleep(10);
    }
}


void MainWindow::walkFangxiangToExit()
{
    //从右边走向出口
    if(ui->car->x() > ui->flagLineFive->x())
    {
        for(int i=ui->car->x(); i-INSTANCE > ui->flagLineFive->x(); --i)
        {
            ui->car->setGeometry(i,ui->car->y(),
                                 ui->car->width(),
                                 ui->car->height()
                                 );
                mysleep(10);
        }
    }else   //从左边走向出口
    {
        for(int i=ui->car->x(); i+INSTANCE < ui->flagLineFive->x(); ++i)
        {
           ui->car->setGeometry(i,ui->car->y(),
                                ui->car->width(),
                                ui->car->height()
                                );
           mysleep(10);
        }
    }
    cout<<"---------------hello--------------------"<<endl;
}
//驶出停车场
void MainWindow::exitPark()
{
    if(ui->car->y() > ui->flagUp->y())//说明在上部分停车
    {
        for(int i=ui->car->y(); i+INSTANCE+ui->car->height() < ui->downStreet->y(); ++i)
        {
            ui->car->setGeometry(ui->car->x(),i,
                                 ui->car->width(),
                                 ui->car->height()
                                 );
                mysleep(10);
        }
     }
     else   //下半部停车
     {
        for(int i=ui->car->y(); i+INSTANCE<ui->upStreet->y(); --i)
        {
            ui->car->setGeometry(ui->car->x(),i,
                                 ui->car->width(),
                                 ui->car->height()
                                 );
            mysleep(10);
        }
     }

    walkFangxiangToExit();
    walkExit();
}











