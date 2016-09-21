#ifndef SLICER_H
#define SLICER_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QImage>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <ringbuffer.h>

class Slicer : public QObject
{   Q_OBJECT
    bool f_stop;
    bool f_loadSuccessful;
    QMutex mutex;
    cv::VideoCapture *capture;
    int frameRate;
    QImage *img;
    cv::Mat frame;
    cv::Mat RGBframe;
    RingBuffer<QImage>* buffer;

public:
    explicit Slicer(RingBuffer<QImage> &buf);
    virtual ~Slicer();
    void bufferingFrame(const QImage &img);
signals:
    void finished();//end of thread, when video is end
    void error(QString err);
public slots:
    void stop();
    void loadVideo(std::string path);
    void process(); //slice video to frame and send to circular buffer

};

#endif // SLICER_H
