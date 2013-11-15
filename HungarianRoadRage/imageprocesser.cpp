#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
    DebugWin.show();
//    BackGroundSubtractor.nmixtures = 3;
//    BackGroundSubtractor.bShadowDetection = false;
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
}

int ImageProcesser::getMove(cv::Mat const &CapturedImage)
{
    cv::cvtColor(CapturedImage,HSVImage,cv::COLOR_BGR2HSV); //Converting to HSV
    //Filtering for object sizes:
//    cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,1));
//    cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,1));
//    cv::erode(HSVImage,OutImage,erodeElement);
//    cv::erode(HSVImage,OutImage,erodeElement);
//    cv::dilate(HSVImage,OutImage,dilateElement);
//    cv::dilate(HSVImage,OutImage,dilateElement);


    cv::Sobel(HSVImage, OutImage, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_CONSTANT);

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
