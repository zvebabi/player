#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    bufferOuter = new RingBuffer<QImage>(BUFFER_SIZE);
    bufferInner = new RingBuffer<QImage>(BUFFER_SIZE);
    SlicerOuter = new Slicer(*bufferOuter);
    SlicerInner = new Slicer(*bufferInner);
    myPlayer = new VideoPlayer(*bufferOuter, *bufferInner);

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                                  this, SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete SlicerOuter;
}

void MainWindow::updatePlayerUI(QImage& img)
{
    if (!img.isNull())
        {
            ui->label->setAlignment(Qt::AlignCenter);
            ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                               Qt::KeepAspectRatio, Qt::FastTransformation));
        }
}
