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
    MODEL/Media.cpp \
    MODEL/SerieTV.cpp \
    MODEL/Film.cpp \
    MODEL/User.cpp \
    MODEL/Database.cpp

HEADERS  += MainWindow.h \
    Media.h \
    MODEL/Media.h \
    MODEL/SerieTV.h \
    MODEL/Film.h \
    MODEL/Container.h \
    MODEL/User.h \
    MODEL/Database.h

FORMS    += MainWindow.ui
