#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QPainter>
#include <algorithm>
#include <memory>
#include <ringbuffer.h>

class VideoPlayer : public QObject
{   Q_OBJECT
    bool f_stop;
    int fpsOut;
    int fpsIn;
    QTime timer;
    RingBuffer<std::shared_ptr<QImage>>* bufferOut; //for outer video
    RingBuffer<std::shared_ptr<QImage>>* bufferIn; //for inner video

public:
    explicit VideoPlayer(RingBuffer<std::shared_ptr<QImage> > *bufOut, RingBuffer<std::shared_ptr<QImage> > *bufIn);
    virtual ~VideoPlayer();
    void setStop(bool value);
    void setFPSOut(int n) {fpsOut = n;}
    void setFPSIn(int n) {fpsIn = n;}
signals:
    void processedImage(QImage img);
    void finished();
public slots:
    void process(); //concat 2 video frame and show
};

#endif // VIDEOPLAYER_H
