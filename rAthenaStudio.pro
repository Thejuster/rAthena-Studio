#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T12:23:34
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rAthenaStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hostconfig.cpp

HEADERS  += mainwindow.h \
    hostconfig.h

FORMS    += mainwindow.ui \
    hostconfig.ui

RESOURCES += \
    data.qrc