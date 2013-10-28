#include "mainwindow.h"
#include <QApplication>
//#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
//#include "RaceRoad.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//        cv::Mat image;
//        image = cv::imread("debug/images/kep.png");
//        cvNamedWindow("hello");
//        cv::imshow("hello",image);

//        cvWaitKey(0);
//    RaceRoad* testRoad = new RaceRoad();
//    testRoad -> play();

//    delete testRoad;
    return a.exec();
}
