#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myPlayer = new Slicer(BUFFER_SIZE);
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage&)),
                              this, SLOT(updatePlayerUI(QImage&)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myPlayer;
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
