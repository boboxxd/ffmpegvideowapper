#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T09:10:50
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ffmpegdemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    hhvideostream.cpp \
    hhvideowidget.cpp \
    hhvideoalarm.cpp

HEADERS += \
        widget.h \
    hhvideostream.h \
    hhvideowidget.h \
    hhvideoalarm.h


INCLUDEPATH += /home/hhit/lib/ffmpeg-release/include
INCLUDEPATH += $$PWD/include
LIBS += -L/home/hhit/lib/ffmpeg-release/lib -lavcodec -lavformat -lswscale -lavdevice -lavfilter -lavutil -lswresample
LIBS += -L$$PWD/lib/ -lhhclient
