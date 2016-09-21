#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <ringbuffer.h>

class VideoPlayer : public QObject
{   Q_OBJECT
    bool f_stop;
    RingBuffer<QImage>* bufferOut; //for outer video
    RingBuffer<QImage>* bufferIn; //for inner video

public:
    explicit VideoPlayer(RingBuffer<QImage> &bufOut, RingBuffer<QImage> &bufIn);
    virtual ~VideoPlayer();
signals:
    void processedImage(QImage img);
    void finished();
public slots:
    void stop();
    void process(); //concat 2 video frame and show
};

#endif // VIDEOPLAYER_H
