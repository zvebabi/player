#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define BUFFER_SIZE 500

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <slicer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void updatePlayerUI(QImage &img);
private:
    Ui::MainWindow *ui;
    Slicer *myPlayer;
};

#endif // MAINWINDOW_H
