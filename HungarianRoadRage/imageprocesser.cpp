#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
    DebugWin.show();
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Width: " << SizeOfCamera.width <<std::endl;
}

int ImageProcesser::getMove(cv::Mat const &CapturedImage)
{
    cv::cvtColor(CapturedImage,HSVImage,cv::COLOR_BGR2HSV); //Converting to HSV
    cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(8,8));
    cv::erode(HSVImage,HSVImage,erodeElement);
    cv::erode(HSVImage,HSVImage,erodeElement);
    cv::dilate(HSVImage,HSVImage,dilateElement);
    cv::dilate(HSVImage,HSVImage,dilateElement);

    //Put the output to the debug window
    cv::resize(HSVImage, HSVImage, cv::Size(480,300), 0, 0, cv::INTER_CUBIC);
    cv::flip(HSVImage, HSVImage, 1);
    QImage DebugImage((uchar*)HSVImage.data,
                         HSVImage.cols,
                         HSVImage.rows,
                         HSVImage.step,
                         QImage::Format_RGB888);
    DebugWin.setDebugVideo(DebugImage);
    std::cerr << "Processing..." <<std::endl;
    return 0;
}
