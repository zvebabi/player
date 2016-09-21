#include "videoplayer.h"

VideoPlayer::VideoPlayer(RingBuffer<QImage> &bufOut, RingBuffer<QImage> &bufIn)
{
    f_stop = true;
    *bufferIn = bufOut;
    *bufferOut = bufIn;
}

VideoPlayer::~VideoPlayer()
{
    delete bufferIn;
    delete bufferOut;
}

void VideoPlayer::stop()
{
    f_stop = true;
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
        bufferIn->popElement(img);
        emit processedImage(img);
    }
    emit finished();
}
