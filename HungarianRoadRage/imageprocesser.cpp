#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    IsFirst = true;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
}

int ImageProcesser::getMove(cv::Mat CapturedImage)
{
    if(CapturedImage.empty()) {std::cout << "Baj van..." << std::endl; return 0;}
    ProcessingTimer.start();
//    if(IsFirst)
//    {
//        CapturedImage.copyTo(FirstImage);
//        cv::cvtColor(FirstImage, FirstImage, CV_BGR2GRAY);
//        IsFirst = false;
//    }

//    CapturedImage.copyTo(OutImage);
/*
 *Threshold detection
 */
//    cv::cvtColor(OutImage, OutImage, CV_BGR2GRAY);
//    cv::GaussianBlur(OutImage, OutImage,cv::Size(9,9),2,2);
//    cv::threshold(OutImage,ProcessingImage,110,255,cv::THRESH_BINARY);
//    cv::integral(OutImage,ProcessingImage,SqSumImage,-10);
//    cv::absdiff(ProcessingImage, FirstImage, ProcessingImage);
//    CapturedImage.copyTo(ProcessingImage);
//    ProcessingImage.copyTo(OutImage);
/*
 *Threshold detection end
 */

/*
 *Color tracking
 */

    cv::cvtColor(CapturedImage,HSVImage,CV_BGR2HSV_FULL);
    cv::GaussianBlur(HSVImage, HSVImage,cv::Size(9,9),3,3);
    cv::inRange(HSVImage,cv::Scalar(55,55,80),cv::Scalar(255,255,255),ProcessingImage); //for europian human objects
    cv::threshold(ProcessingImage,ProcessingImage,100,200,cv::THRESH_BINARY);



    cv::imshow("Processed", ProcessingImage);
//    cv::imshow("Sq",SqSumImage);
//    cv::imshow("Output", OutImage);

    std::cerr << "Elapsed processer time: "<< ProcessingTimer.elapsed() << " msec" <<std::endl;

    return 0;
}
