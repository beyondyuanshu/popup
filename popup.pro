#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T10:52:33
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = popup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    popup.cpp \
    dialogbase.cpp

HEADERS  += mainwindow.h \
    popup.h \
    dialogbase.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
