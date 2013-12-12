#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    IsFirst = true;

    BSubLeft.set("nmixtures",3);
    BSubLeft.set("detectShadows", false);

    BSubRight.set("nmixtures",3);
    BSubRight.set("detectShadows", false);

    LeftROI = cv::Rect(0, 10, 110, 130);
    RightROI = cv::Rect(250,0,100,130);
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
}

int ImageProcesser::getMove(cv::Mat CapturedImage)
{
    if(CapturedImage.empty()) {std::cout << "Baj van..." << std::endl; return 0;}
    ProcessingTimer.start();

    CapturedImage.copyTo(OutImage);

    /*
     *Cropping the hands
     */

    LeftHand = OutImage(LeftROI);
    cv::imshow("LeftHand",LeftHand);
    RightHand = OutImage(RightROI);
    cv::imshow("RightHand",RightHand);

  /*
   *Background subtraction
   */
    //Left hand
    BSubLeft.operator ()(LeftHand,ForeGroundLeft);
    cv::GaussianBlur(ForeGroundLeft, ForeGroundLeft,cv::Size(9,9),5,5);
    cv::threshold(ForeGroundLeft,ForeGroundLeft,100,255,cv::THRESH_BINARY);
    cv::adaptiveThreshold(ForeGroundLeft,ForeGroundLeft,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,7,0.1);
//    cv::imshow("Left",ForeGroundLeft);

    //Right hand
    BSubRight.operator ()(RightHand,ForeGroundRight);
    cv::GaussianBlur(ForeGroundRight, ForeGroundRight,cv::Size(9,9),5,5);
    cv::threshold(ForeGroundRight,ForeGroundRight,100,255,cv::THRESH_BINARY);
    cv::adaptiveThreshold(ForeGroundRight,ForeGroundRight,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,7,0.1);
//    cv::imshow("Right",ForeGroundRight);

//    std::cerr << "Nonzero: " << 14300 - cv::countNonZero(ForeGroundLeft) << std::endl;
//    std::cerr << "Elapsed processer time: "<< ProcessingTimer.elapsed() << " msec" <<std::endl;

    if(14300 - cv::countNonZero(ForeGroundLeft) > 1500) return -1;
    if(13000 - cv::countNonZero(ForeGroundRight) > 1200) return 1;

    return 0;
}
