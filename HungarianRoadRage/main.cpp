#include "mainwindow.h"
#include <QApplication>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();
    try{
        cv::Mat mat;
        mat = cv::imread("kep.jpg");
        cvNamedWindow("hello");
        cv::imshow("hello",mat);

        cvWaitKey(0);
    }catch(cv::Exception e){
        //e.msg();
    }

    return 0;
//Hello
    //return a.exec();
}
