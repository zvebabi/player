#include "slicer.h"

Slicer::Slicer(RingBuffer<QImage>* buf)
{
    f_stop = true;
    buffer = buf;
}

Slicer::~Slicer()
{
    qDebug() << "slicer end";
}

bool Slicer::isVideoLoaded()
{
    return f_loadSuccessful;
}

void Slicer::setStop(bool value)
{
    f_stop = value;
}

void Slicer::loadVideo(QString path)
{
    capture = new cv::VideoCapture(path.toUtf8().data());
    if (capture->isOpened()) {
        frameRate = (int)capture->get(CV_CAP_PROP_FPS);
        f_loadSuccessful = true;
    }
    else {
        f_loadSuccessful = false;
    }
}

void Slicer::process()
{
    qDebug() << "buf_process..";
    bool notFull = true; //flag for overloaded buffer
    while(!f_stop){
        if (notFull)
        {
            if (!capture->read(frame))
            {
                f_stop = true;
            }
            if (frame.channels()== 3){
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = new QImage((const unsigned char*)(RGBframe.data),
                                  RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            }
            else
            {
                img = new QImage((const unsigned char*)(frame.data),
                                     frame.cols,frame.rows,QImage::Format_Indexed8);
            }
//            qDebug() << "bufferingFrame" << img;
            notFull = buffer->insertElement(*img);
        }
        else
        {
//            qDebug() << "buffer_full" << img;
            QThread::msleep(10);
            notFull = buffer->insertElement(*img);
        }
    }

    //Clean memory
    capture->release();
    delete capture;
    delete img;

    emit finished();
}


