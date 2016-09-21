#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include <ringbuffer.h>
#include <slicer.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    RingBuffer<int*> *test = new RingBuffer<int*>(15);


    for (int i=0; i<10; i++) {
        int *k = new int (i);
        if (test->insertElement(k) == false) {
            qDebug() << i << "false";
        }
    }

    for (int i=0; i<5; i++) {

        int *k = new int;
        k = test->popElement(k);

        if (k==NULL) {
            qDebug() << "Empty buffer";
        }
        else {
            qDebug() << "pop" << *k;
        }
    }
    delete test;

    w.show();

    return a.exec();
}
