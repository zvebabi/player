#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T19:59:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app

win32 {
    message(win32_libs)
    INCLUDEPATH += C:\opencvMingw\x64\install\include
    LIBS += -L"C:\opencvMingw\x64\install\x64\mingw\bin"
    LIBS += -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
