/*#include "mainwindow.h"
#include <QApplication>
//#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
//#include "RaceRoad.hpp"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
        cv::Mat image;
        image = cv::imread("debug/images/kep.png");
        cvNamedWindow("hello");
        cv::imshow("hello",image);

//        cvWaitKey(0);
//    RaceRoad* testRoad = new RaceRoad();
//    testRoad -> play();

//    delete testRoad;
    return 0;//a.exec();
}*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

if (!stream1.isOpened()) { //check if video device has been initialised
cout << "cannot open camera";
}

//unconditional loop
while (true) {
Mat cameraFrame;
stream1.read(cameraFrame);
imshow("cam", cameraFrame);
if (waitKey(30) >= 0)
break;
}
return 0;
}
