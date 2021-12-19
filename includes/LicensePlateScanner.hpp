#pragma once

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace cv;
using namespace cv::dnn;

class LicensePlateScanner {
    public:
        /*
        * Scans a file that contains the image with plate number
            * @param filename A string containing the directory of the file to be read from
            * @return a string containing the plate number detected
        */
        static std::string GetPlateNumber(std::string filename);

        /*
        * A helper function used to decode an image 
        * @param scores : help to define contours covering text 
        * @param scoreThresh : help to define contours covering text
        * @param detections : help to define contours covering text
        * @param confidences : help to define contours covering text
        */        
        static void decode(const Mat& scores, const Mat& geometry, float scoreThresh, std::vector<RotatedRect>& detections, std::vector<float>& confidences);
};