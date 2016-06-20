#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T10:07:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Halvarsson_client
TEMPLATE = app


SOURCES += main.cpp\
        halvarsson_client.cpp \
    table.cpp \
    order.cpp \
    attribute.cpp \
    clickablelabel.cpp

HEADERS  += halvarsson_client.h \
    table.h \
    order.h \
    attribute.h \
    clickablelabel.h

FORMS    += halvarsson_client.ui \
    table.ui \
    order.ui \
    attribute.ui

CONFIG += mobility c++11

RESOURCES += \
    icons.qrc


