#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T19:29:55
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuIBE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maincontrol.cpp \
    messagedialog.cpp \
    comunicacaoserial.cpp \
    serialconfig.cpp

HEADERS  += mainwindow.h \
    maincontrol.h \
    messagedialog.h \
    comunicacaoserial.h \
    serialconfig.h

FORMS    += mainwindow.ui \
    messagedialog.ui

RESOURCES += \
    images.qrc
