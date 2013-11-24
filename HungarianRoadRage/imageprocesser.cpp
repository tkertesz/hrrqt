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
    if(IsFirst)
    {
        CapturedImage.copyTo(FirstImage);
        cv::cvtColor(FirstImage, FirstImage, CV_BGR2GRAY);
        IsFirst = false;
    }

    CapturedImage.copyTo(OutImage);
    cv::cvtColor(OutImage, OutImage, CV_BGR2GRAY);
    cv::GaussianBlur(OutImage, OutImage,cv::Size(9,9),2,2);
    cv::absdiff(OutImage, FirstImage, ProcessingImage);
//    CapturedImage.copyTo(ProcessingImage);
//    ProcessingImage.copyTo(OutImage);
    //Circle
//    cv::GaussianBlur(ProcessingImage, ProcessingImage,cv::Size(9,9),2,2);
//    cv::HoughCircles(ProcessingImage, circles, CV_HOUGH_GRADIENT, 1, ProcessingImage.rows/8, 100, 50, 0, 0);

//   for( size_t i = 0; i < circles.size(); i++ )
//     {
//         cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//         int radius = cvRound(circles[i][2]);
//         // circle center
//         cv::circle(OutImage, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
//         // circle outline
//         cv::circle(OutImage, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
//      }


    cv::imshow("Processed", ProcessingImage);
//    cv::imshow("Output", OutImage);

    std::cerr << "Processing..." <<std::endl;
    return 0;
}
