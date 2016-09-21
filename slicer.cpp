#include "slicer.h"

Slicer::Slicer(int sizeOfBuffer)
{
    f_stop = true;
    buffer = new RingBuffer<QImage>(sizeOfBuffer);
}

Slicer::~Slicer()
{
    capture->release();
    delete capture;
    delete buffer;
    delete img;
}

void Slicer::bufferingFrame(const QImage &img)
{
    qDebug() << "bufferingFrame";
    buffer->insertElement(img);
    emit processedImage(img);
}

void Slicer::stop()
{
    f_stop = true;
}

void Slicer::loadVideo(std::string path)
{
    capture->open(path);
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
    qDebug() << "process..";
    while(!f_stop){
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
        bufferingFrame(*img);

    }
}


