#ifndef IMAGEPROCESSER_H
#define IMAGEPROCESSER_H

#include <QElapsedTimer>
#include <iostream>
#include <algorithm>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/cv.h"
#include "opencv2/video/video.hpp"

/*
 *ImageProcesser class for processing the captured video from the wabcamera to controll the car's behaviour.
 *
 *Output: 0: no move, 1 right, -1 left
 *
 */
class ImageProcesser
{
private:
    cv::Size SizeOfCamera;
    cv::Mat ProcessingImage;
    cv::Mat OutImage;
    cv::Mat HSVImage;
    cv::Mat AvgImage;
    cv::Mat TresholdImage;
    cv::Mat SqSumImage;
    cv::Mat FirstImage;
    cv::Mat ForeGround;
    cv::Mat BackGround;

    QElapsedTimer ProcessingTimer;

    cv::BackgroundSubtractorMOG2 BSub;

    bool IsFirst;

//    std::vector<cv::Vec3f> circles;

public:
    ImageProcesser(cv::Size camsize);
    void setCamSize(cv::Size camsize);
    int getMove(cv::Mat CapturedImage); //Output: 0: no move, 1 right, 2 left
};

#endif // IMAGEPROCESSER_H
