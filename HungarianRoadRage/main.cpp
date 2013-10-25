#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();
        cv::Mat image;
        image = cv::imread("debug/images/kep.png");
        cvNamedWindow("hello");
        cv::imshow("hello",image);

        cvWaitKey(0);

    return 0;
//Hello
    //return a.exec();
}
