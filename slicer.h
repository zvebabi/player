#ifndef SLICER_H
#define SLICER_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>

class Slicer : public QObject
{   Q_OBJECT
    cv::VideoCapture capture;
    int frameRate;
    QImage img;
    cv::Mat frame;
    cv::Mat RGBframe;

public:
    Slicer();
    virtual ~Slicer();
signals:
    void bufferingFrame(const QImage &img); //emit to circular buffer
    void finished();//end of thread, when video is end
    void error(QString err);
public slots:
   // void loadVideo(QString path);
   // void process(); //slice video to frame and send to circular buffer

};

#endif // SLICER_H
