#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T21:21:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elfview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ElfDataType.cpp

HEADERS  += mainwindow.h \
    dumpcode.h \
    ElfDataType.h \
    ElfHeaderClass.h \
    HeaderClass.h \
    ElfPrgHeaderClass.h \
    ElfSeHeaderClass.h

FORMS    += mainwindow.ui
