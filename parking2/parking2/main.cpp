#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <string>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.run();

    return a.exec();
}
