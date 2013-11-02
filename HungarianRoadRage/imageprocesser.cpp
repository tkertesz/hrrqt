#include "imageprocesser.h"

ImageProcesser::ImageProcesser(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Widht: " << SizeOfCamera.width <<std::endl;
}

void ImageProcesser::setCamSize(cv::Size camsize)
{
    SizeOfCamera = camsize;
    std::cout << "Camera size set to:\n"<< "Height: " << SizeOfCamera.height << ", Widht: " << SizeOfCamera.width <<std::endl;
}

int ImageProcesser::getMove(cv::Mat &CapturedImage)
{
    std::cerr << "Processing..." <<std::endl;
    return 0;
}
