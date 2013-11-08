#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QNetworkInterface>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imageprocesser.h"
#include "network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeVideoStream();
    ~MainWindow();

protected:
    //Handling the key press events
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;

    cv::VideoCapture CaptureCamera;
    cv::Size CamSize;
    cv::Mat OriginalImageMat;
    cv::Mat ProcessedImageMat;
    cv::Mat ResizedImageMat;

    QImage OriginalImage;
    QImage ProcessedImage;
    QImage NetworkImage;

    QTimer* ProcessTimer;

    ImageProcesser* Processer;
    Network* n;

    QString MyIpAddr;

public slots:
    void processVideoAndUpdateQUI();

};

#endif // MAINWINDOW_H
