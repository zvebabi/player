#include "videoplayer.h"

VideoPlayer::VideoPlayer(RingBuffer<QImage> *bufOut, RingBuffer<QImage> *bufIn)
{
    f_stop = true;
    bufferIn = bufIn;
    bufferOut = bufOut;
}

VideoPlayer::~VideoPlayer()
{
    qDebug() << "vidplayer end";
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
    QThread::msleep(400); //pause before buffer will init
    QImage img;
    QImage img2;
    while(!f_stop)
    {
        timer.start();
        if (!bufferOut->popElement(img)
            || !bufferIn->popElement(img2))
        {
            QThread::msleep(1);
            continue;
        }

        //make frame in frame
        img2 = img2.scaled(img.width()/2,img.height()/2,
                    Qt::KeepAspectRatio, Qt::FastTransformation);
        int dx = (img.width() - img2.width())/2;
        int dy = (img.height() - img2.height())/2;
        QPainter p(&img);
        p.drawImage(dx, dy, img2);
        p.end();

        //send frame to screen
        if (!img.isNull())
            emit processedImage(img);

        //dynamically fps delay
        int delay = 1000/fpsOut-timer.elapsed(); //
        QThread::msleep(delay > 0 ? delay : 0 );
    }


    emit finished();
}
