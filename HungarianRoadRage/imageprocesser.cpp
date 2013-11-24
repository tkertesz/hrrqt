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

int ImageProcesser::getMove(cv::Mat CapturedImage)
{
    if(CapturedImage.empty()) std::cout << "Baj van..." << std::endl;
    cv::cvtColor(CapturedImage, ProcessingImage, CV_BGR2GRAY);
    ProcessingImage.copyTo(OutImage);

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
