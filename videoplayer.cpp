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
    QThread::msleep(400); //delayed start for buffer initialisation

    //sync different fps
    int maxFps = std::max(fpsOut,fpsIn);
    int ratio = maxFps/std::min(fpsOut,fpsIn);
    int modulo = maxFps%std::min(fpsOut,fpsIn);
    int framecounter = maxFps; // count from maxfps to zero
    int i=ratio, k=modulo; //frame repeate counters
    bool oneMoreTimes = false; // for modulo frame
    QImage img;
    QImage img2;
    while(!f_stop)
    {
        timer.start();
        //sync algorithm for outer video
        if (fpsOut != maxFps) //fpsOut less than fpsIn
        {
            bufferIn->popElement(img2);
            if (i<ratio)
                ++i;
            else if (oneMoreTimes && k>0)
            {
                oneMoreTimes=false;
                --k;
            }
            else
            {
                bufferOut->popElement(img);
                oneMoreTimes=true;
                i=1;
            }
        }
        else if (fpsIn != maxFps)  // fpsIn less than fpsOut
        {
            bufferOut->popElement(img);
            if (i<ratio)
                ++i;
            else if (oneMoreTimes && k>0)
            {
                oneMoreTimes=false;
                --k;
            }
            else
            {
                bufferIn->popElement(img2);
                oneMoreTimes=true;
                i=1;
            }
        }
        else //both fps are equal. normal mode
        {
            if (!bufferOut->popElement(img)
                || !bufferIn->popElement(img2))
            {
                QThread::msleep(1);
                qDebug() << "buffer err";
                continue;
            }
        }
        //restart counter each second
        if (--framecounter == 0)
        {
            framecounter = maxFps;
            k=modulo;
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
        int delay = 1000/maxFps-timer.elapsed(); //
        QThread::msleep(delay > 0 ? delay : 0 );
    }
    emit finished();
}
