#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T12:23:34
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rAthenaStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hostconfig.cpp \
    databasedump.cpp \
    advancesetting.cpp \
    serverstart.cpp \
    NPC/npceditor.cpp \
    NPC/nodeeditor.cpp

HEADERS  += mainwindow.h \
    hostconfig.h \
    databasedump.h \
    advancesetting.h \
    serverstart.h \
    NPC/npceditor.h \
    NPC/nodeeditor.h

FORMS    += mainwindow.ui \
    hostconfig.ui \
    databasedump.ui \
    advancesetting.ui \
    serverstart.ui \
    NPC/npceditor.ui

RESOURCES += \
    data.qrc


