#include "videoplayer.h"

VideoPlayer::VideoPlayer(RingBuffer<QImage> *bufOut, RingBuffer<QImage> *bufIn)
{
    f_stop = true;
    bufferIn = bufOut;
    bufferOut = bufIn;
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::setStop(bool value)
{
    f_stop = value;
}

/*
 * concatenate two image and emit result in ui with right fps
 */
void VideoPlayer::process()
{
    qDebug() << "player_process..";
    while(!f_stop)
    {
        QImage img;
        QImage img2;
        img = bufferIn->popElement(img);
        img2 = bufferIn->popElement(img2);
        if (img.isNull())
        {
            qDebug() << "buffer empty..sleep";
            QThread::msleep(500);
        }
        else
        {
            emit processedImage(img);
        }
    }
    emit finished();
}
