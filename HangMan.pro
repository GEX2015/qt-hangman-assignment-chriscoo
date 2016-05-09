#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T11:35:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HangMan
TEMPLATE = app


SOURCES += main.cpp\
        View/view.cpp

HEADERS  +=  View/view.h\

FORMS    +=  View/view.ui\


INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"


LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"
