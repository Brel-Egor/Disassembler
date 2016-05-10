#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T23:36:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zapiska
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dl.cpp \
    find_helper.cpp \
    res_ins.cpp

HEADERS  += mainwindow.h \
    dl.h \
    find_helper.h \
    res_ins.h \
    table_for_ld.h

FORMS    += mainwindow.ui
