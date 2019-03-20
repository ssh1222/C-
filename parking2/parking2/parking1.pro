#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T18:29:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parking1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sql.cpp \
    modifyfile.cpp

HEADERS  += mainwindow.h \
    sql.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
