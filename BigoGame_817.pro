#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T22:50:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigoGame_v1.0
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    Bobject/bobject.cpp \
    Bobject/bimage.cpp \
    Bobject/btext.cpp \
    Bobject/brect.cpp \
    Bobject/bellipse.cpp \
    Bobject/bline.cpp \
    Bgame/tank/tank.cpp \
    Bobject/bdynobj.cpp \
    Bgame/tank/tankwidget.cpp \
    Bobject/bglobalobjs.cpp \
    Bgame/tank/bullet.cpp \
    Bobject/bdynamic.cpp \
    Bobject/bstatic.cpp \
    Bobject/bbasewidget.cpp \
    Bgame/tank/tdyncommon.cpp \
    Bgame/tank/explope.cpp \
    Bgame/tank/tbrick.cpp

HEADERS  += widget.h \
    Bobject/btypes.h \
    bobject.h \
    Bobject/bobject.h \
    Bobject/bdynaction.h \
    Bobject/bimage.h \
    Bobject/btext.h \
    Bobject/brect.h \
    Bobject/bellipse.h \
    Bobject/Bobjects.h \
    Bobject/bline.h \
    Bgame/tank/tank.h \
    Bobject/bdynobj.h \
    gamedata.h \
    Bgame/tank/tankwidget.h \
    Bobject/bglobalobjs.h \
    Bgame/tank/bullet.h \
    Bobject/bdynamic.h \
    Bobject/bstatic.h \
    Bobject/bbasewidget.h \
    Bgame/tank/tdyncommon.h \
    Bgame/tank/explope.h \
    Bgame/tank/tbrick.h

FORMS    +=
