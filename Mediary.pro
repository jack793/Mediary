#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T16:16:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mediary
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Media.cpp \
    MODEL/Media.cpp

HEADERS  += MainWindow.h \
    Media.h \
    MODEL/Media.h

FORMS    += MainWindow.ui
