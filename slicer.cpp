#include "slicer.h"

Slicer::Slicer(RingBuffer<QImage>* buf)
{
    f_stop = true;
    buffer = buf;
}

Slicer::~Slicer()
{
    qDebug() << "slicer end";
    //Clean memory
    capture->release();
    delete capture;
    delete img;
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
        pathToVideo = path; //save video file
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
                loadVideo(pathToVideo);  // reload video while EOF
                continue;
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
            notFull = buffer->insertElement(*img);
            QThread::msleep(1);
        }
        else
        {
            QThread::msleep(20);
            notFull = buffer->insertElement(*img);
        }
    }


    emit finished();
}


