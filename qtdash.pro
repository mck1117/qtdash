#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T03:50:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtdash
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    can/BeagleboneCanInterface.cpp \
    can/CanInterface.cpp

HEADERS  += mainwindow.h \
    can/BeagleboneCanInterface.h \
    can/CanInterface.h

FORMS    += mainwindow.ui

CONFIG += c++11
