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
    can/SerialCanInterface.cpp \
    can/CanInterface.cpp \
    config/JsonConfigured.cpp \
    data/DataChannel.cpp \
    data/Converter.cpp \
    data/Limits.cpp \
    data/ChannelProcessor.cpp \
    Logger.cpp

HEADERS  += mainwindow.h \
    can/SerialCanInterface.h \
    can/CanInterface.h \
    config/JsonConfigured.h \
    data/DataChannel.h \
    data/Converter.h \
    data/Limits.h \
    data/ChannelProcessor.h \
    Logger.h

FORMS    += mainwindow.ui

CONFIG += c++11
