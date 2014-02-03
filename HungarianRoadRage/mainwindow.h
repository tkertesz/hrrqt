#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QNetworkInterface>
#include <QGraphicsScene>
#include <QElapsedTimer>
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
    void setIP(QHostAddress myIP, QHostAddress partnerIP);
    void closeVideoStream(); //Release the camera hardware and stopping the processer's timer
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *); //Handling the key press events
    void closeEvent (QCloseEvent *event); //Handling the close event

private:
    Ui::MainWindow *ui;
    void restart();
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
    QHostAddress PartnerIpAddr;

    //Graphics
    QGraphicsScene* scene;
    Car* myCar;
    Road* myRoad;

    //Elapsed timer
    //one more smileyface Tibby and I will ask you personally Y SO SERIOUS
    QElapsedTimer ProcUpdateElapsedTime;

    //Other useful variables
    int lives;
    int distance;
    int prevmove;
    bool gameStarted;

public slots:
    void processVideoAndUpdateQUI();
    void receiveNetworkImage(QImage q);
    void receiveLifeNumber(int i);
    void receiveDistanceNumber(int i);
    void lose();

};

#endif // MAINWINDOW_H
