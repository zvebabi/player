#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include <ringbuffer.h>
#include <slicer.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
