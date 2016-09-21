#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T19:59:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = player
TEMPLATE = app

win32 {
    message(win32_libs)
    INCLUDEPATH += C:\opencvMingw\x64\install\include
    LIBS += -L"C:\opencvMingw\x64\install\x64\mingw\bin"
    LIBS += -lopencv_core2413 -lopencv_video -lopencv_imgproc2413
}
linux {
    message(linux_libs)
    INCLUDEPATH += -L/usr/local/include
    LIBS += -L/usr/local/lib
    LIBS += -lopencv_core -lopencv_video -lopencv_imgproc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    slicer.cpp \
    videoplayer.cpp

HEADERS  += mainwindow.h \
    slicer.h \
    ringbuffer.h \
    videoplayer.h

FORMS    += mainwindow.ui
