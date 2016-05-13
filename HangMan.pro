#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T13:42:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hangman
TEMPLATE = app


SOURCES += main.cpp\
        Controller/mainwindow.cpp \
    Model/hangmanclass.cpp

HEADERS  += Controller/mainwindow.h \
    Model/hangmanclass.h

FORMS    += View/mainwindow.ui

RESOURCES += \
    resources.qrc
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"


LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"
