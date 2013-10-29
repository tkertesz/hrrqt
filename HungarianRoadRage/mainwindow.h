#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //Handling the key press events
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;

    cv::VideoCapture CaptureCamera;
    cv::Mat OriginalImageMat;
    cv::Mat ProcessedImageMat;
    cv::Mat ResizedImageMat;

    QImage OriginalImage;
    QImage ProcessedImage;

    QTimer* ProcessTimer;

public slots:
    void processVideoAndUpdateQUI();

};

#endif // MAINWINDOW_H
