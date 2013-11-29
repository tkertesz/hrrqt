#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QNetworkInterface>
#include <QGraphicsScene>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imageprocesser.h"
#include "network.h"
#include "car.h"
#include "road.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeVideoStream(); //Release the camera hardware and stopping the processer's timer
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *); //Handling the key press events

private:
    Ui::MainWindow *ui;

    //CV
    cv::VideoCapture CaptureCamera;
    cv::Size CamSize;
    cv::Mat OriginalImageMat;
    cv::Mat ProcessedImageMat;
    cv::Mat ResizedImageMat;

    //Images
    QImage OriginalImage;
    QImage ProcessedImage;
    QImage NetworkGetImage;
    QImage NetworkSendImage;

    //Timers
    QTimer* ProcessTimer;
    QTimer timer;
    QBasicTimer timer2;

    ImageProcesser* Processer;
    Network* n;

    QHostAddress MyIpAddr;

    //Graphics
    QGraphicsScene* scene;
    Car* myCar;
    Road* myRoad;

    //Other useful variables :)
    bool NetworkStarted;
    int lives;
    int distance;

public slots:
    void processVideoAndUpdateQUI();
    void receiveNetworkImage(QImage q);
    void receiveLifeNumber(int i);
    void receiveDistanceNumber(int i);
    void lose(bool isWin);

};

#endif // MAINWINDOW_H
