#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
    DebugWin.show();
    BackGroundSubtractor.set("nmixtures",3);
    BackGroundSubtractor.set("detectShadows", false);
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
}

int ImageProcesser::getMove(cv::Mat const &CapturedImage)
{
//    cv::cvtColor(CapturedImage,HSVImage,cv::COLOR_BGR2HSV); //Converting to HSV
    //Filtering for object sizes:
//    cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,1));
//    cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,1));
//    cv::erode(HSVImage,OutImage,erodeElement);
//    cv::erode(HSVImage,OutImage,erodeElement);
//    cv::dilate(HSVImage,OutImage,dilateElement);
//    cv::dilate(HSVImage,OutImage,dilateElement);

//Background removing
    CapturedImage.copyTo(OutImage);
    BackGroundSubtractor.operator ()(CapturedImage,Foreground);
    BackGroundSubtractor.getBackgroundImage(Background);
    cv::erode(Foreground,Foreground,cv::Mat());
    cv::dilate(Foreground,Foreground,cv::Mat());
    cv::findContours(Foreground,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    cv::drawContours(OutImage,contours,-1,cv::Scalar(0,0,255),2);


//    cv::Sobel(HSVImage, OutImage, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_CONSTANT);


    //Put the output to the debug window
    cv::resize(OutImage, OutImage, cv::Size(480,300), 0, 0, cv::INTER_CUBIC);
    cv::flip(OutImage, OutImage, 1);
    QImage DebugImage((uchar*)OutImage.data,
                         OutImage.cols,
                         OutImage.rows,
                         OutImage.step,
                         QImage::Format_RGB888);
    DebugWin.setDebugVideo(DebugImage);
    std::cerr << "Processing..." <<std::endl;
    return 0;
}
