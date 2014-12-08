#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T21:11:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataRecg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpcommand.cpp \
    udpreceive.cpp \
    qpackage.cpp \
    package.cpp \
    qframedata.cpp \
    filesave.cpp



HEADERS  += mainwindow.h \
    tcpcommand.h \
    udpreceive.h \
    qpackage.h \
    package.h \
    qframedata.h \
    filesave.h



FORMS    += mainwindow.ui
