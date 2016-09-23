#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    bufferOuter = new RingBuffer<QImage>(BUFFER_SIZE);
    bufferInner = new RingBuffer<QImage>(BUFFER_SIZE);
    SlicerOuter = new Slicer(bufferOuter);
    SlicerInner = new Slicer(bufferInner);
    myPlayer = new VideoPlayer(bufferOuter, bufferInner);

    //create threads
    thread1 = new QThread; //outer
    thread2 = new QThread; //inner
    thread3 = new QThread; //player

    //show image on label
    connect(myPlayer, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));
    //load video to slicer
    connect(this, SIGNAL(loadVideoOuter(QString)),
                     SlicerOuter, SLOT(loadVideo(QString)));
    connect(this, SIGNAL(loadVideoInner(QString)),
                     SlicerInner, SLOT(loadVideo(QString)));

    // start process() while thread is started
    connect(thread1, SIGNAL(started()), SlicerOuter, SLOT(process()));
    connect(thread2, SIGNAL(started()), SlicerInner, SLOT(process()));
    connect(thread3, SIGNAL(started()), myPlayer, SLOT(process()));

    // delete worker after end of process
    connect(SlicerOuter, SIGNAL(finished()), thread1, SLOT(quit()));
    connect(SlicerOuter, SIGNAL(finished()), SlicerOuter, SLOT(deleteLater()));
    connect(SlicerInner, SIGNAL(finished()), thread2, SLOT(quit()));
    connect(SlicerInner, SIGNAL(finished()), SlicerInner, SLOT(deleteLater()));
    connect(myPlayer, SIGNAL(finished()), thread3, SLOT(quit()));
    connect(myPlayer, SIGNAL(finished()), myPlayer, SLOT(deleteLater()));

    // delete threads
    connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));
    connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));
    connect(thread3, SIGNAL(finished()), thread3, SLOT(deleteLater()));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDebug() << "deleted mainwindow";
    delete ui;
    delete bufferOuter;
    delete bufferInner;
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
        {
//            qDebug() << "take a frame";
            ui->label->setAlignment(Qt::AlignCenter);
            ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                               Qt::KeepAspectRatio, Qt::FastTransformation));
        }
}

void MainWindow::on_btnLoadVideo1_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open File 1");
    //say frameRate to player;
    cv::VideoCapture capture(str.toUtf8().data());
    if (capture.isOpened())
        myPlayer->setFPSOut((int)capture.get(CV_CAP_PROP_FPS));
    emit loadVideoOuter(str);
}

void MainWindow::on_btnLoadVideo2_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open File 2");
    //say frameRate to player;
    cv::VideoCapture capture(str.toUtf8().data());
    if (capture.isOpened())
        myPlayer->setFPSIn((int)capture.get(CV_CAP_PROP_FPS));
    emit loadVideoInner(str);
}

void MainWindow::on_btnPlayVideo_clicked()
{
    if (SlicerOuter->isVideoLoaded()
            && SlicerInner->isVideoLoaded())
    {
        //change flags for start work
        SlicerOuter->setStop(false);
        SlicerInner->setStop(false);
        myPlayer->setStop(false);

        SlicerOuter->moveToThread(thread1);
        SlicerInner->moveToThread(thread2);
        myPlayer->moveToThread(thread3);
        //start threads
        thread1->start();
        thread2->start();
        thread3->start();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Video not loaded!");
        msgBox.exec();
        qDebug() << "video not loaded";
    }
}

void MainWindow::on_btnStopVideo_clicked()
{
    //change flags for stop work
    SlicerOuter->setStop(true);
    SlicerInner->setStop(true);
    myPlayer->setStop(true);
}
