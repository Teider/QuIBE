#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T19:29:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuIBE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maincontrol.cpp \
    messagedialog.cpp

HEADERS  += mainwindow.h \
    maincontrol.h \
    messagedialog.h

FORMS    += mainwindow.ui \
    messagedialog.ui
