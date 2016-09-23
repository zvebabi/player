#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QDebug>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <ringbuffer.h>
#include <videoplayer.h>
#include <slicer.h>


static const int BUFFER_SIZE = 300;


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void loadVideoOuter(QString);
    void loadVideoInner(QString);
private slots:
    void updatePlayerUI(QImage img);
    void on_btnLoadVideo1_clicked();
    void on_btnLoadVideo2_clicked();
    void on_btnPlayVideo_clicked();
    void on_btnStopVideo_clicked();
private:
    Ui::MainWindow *ui;
    RingBuffer<QImage> *bufferOuter;
    RingBuffer<QImage> *bufferInner;
    Slicer *SlicerOuter;
    Slicer *SlicerInner;
    VideoPlayer *myPlayer;
    QThread *thread1;
    QThread *thread2;
    QThread *thread3;
};

#endif // MAINWINDOW_H
