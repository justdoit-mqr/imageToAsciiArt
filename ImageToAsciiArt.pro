#-------------------------------------------------
#
# Project created by QtCreator 2017-07-27T14:08:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageToAsciiArt
TEMPLATE = app


SOURCES += main.cpp\
        imgtoasciiwidget.cpp \
    imgtoasciiart.cpp

HEADERS  += imgtoasciiwidget.h \
    imgtoasciiart.h

RESOURCES += \
    image.qrc

DISTFILES += \
    readme.md
