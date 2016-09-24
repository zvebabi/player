#ifndef SLICER_H
#define SLICER_H

#include <QObject>
#include <QMutex>
#include <QImage>
#include <QThread>
#include <QDebug>
#include <QString>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <ringbuffer.h>

class Slicer : public QObject
{   Q_OBJECT
    bool f_stop;
    bool f_loadSuccessful;
    QString pathToVideo;
    QMutex mutex;
    cv::VideoCapture *capture;
    int frameRate;
    QImage *img;
    cv::Mat frame;
    cv::Mat RGBframe;
    RingBuffer<QImage>* buffer;

public:
    explicit Slicer(RingBuffer<QImage> *buf);
    virtual ~Slicer();
    bool isVideoLoaded();
    void setStop(bool value);
signals:
    void finished();//end of thread, when video is end
public slots:
    void loadVideo(QString path);
    void process(); //slice video to frame and send to circular buffer

};

#endif // SLICER_H
