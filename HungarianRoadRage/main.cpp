#include "mainwindow.h"
#include <QApplication>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

/*Feli volt
  Tibi volt
*/

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();
    cv::Mat mat;
        mat = cv::imread("/Users/hummerdikk/Desktop/tmobile.png");
        cvNamedWindow("hello");
        cv::imshow("hello",mat);

        cvWaitKey(0);
    return 0;
//Hello
    //return a.exec();
}
