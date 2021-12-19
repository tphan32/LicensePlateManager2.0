/*
*   The code is inspired by 
*   https://github.com/spmallick/learnopencv/blob/master/TextDetectionEAST/textDetection.cpp
*   https://tesseract-ocr.github.io/tessdoc/Examples_C++.html
*/

#include "LicensePlateScanner.hpp"
std::string LicensePlateScanner::GetPlateNumber(std::string filename) {
    // Load network
    String model = "frozen_east_text_detection.pb";
    CV_Assert(!model.empty()); 
    Net net = readNet(model);

    // Set up configurations for the network
    std::vector<Mat> output;
    std::vector<String> outputLayers(2);
    outputLayers[0] = "feature_fusion/Conv_7/Sigmoid";
    outputLayers[1] = "feature_fusion/concat_3";

    float confThreshold = 0.5;
    float nmsThreshold = 0.4;
    int inpWidth = 320;
    int inpHeight = 320;

    Mat blob;
    Mat frame = imread(filename);
    blobFromImage(frame, blob, 1.0, Size(inpWidth, inpHeight), Scalar(123.68, 116.78, 103.94), true, false);
    net.setInput(blob);
    net.forward(output, outputLayers);

    Mat scores = output[0];
    Mat geometry = output[1];

    // Decode predicted bounding boxes.
    std::vector<RotatedRect> boxes;
    std::vector<float> confidences;
    decode(scores, geometry, confThreshold, boxes, confidences);

    // Apply non-maximum suppression procedure.
    std::vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);

    // Used to crop region of interset
    Rect rect;
    Mat roiImg;
    Point2f verROI;
    int wid, hei;

    // Render detections.
    Point2f ratio((float)frame.cols / inpWidth, (float)frame.rows / inpHeight);
    int maxArea = 0;
    for (size_t i = 0; i < indices.size(); ++i) {
        RotatedRect& box = boxes[indices[i]];
        Point2f vertices[4];
        box.points(vertices);
        for (int j = 0; j < 4; ++j) {
            vertices[j].x *= ratio.x;
            vertices[j].y *= ratio.y;
        }

        // Extend the box to the correct width and height
        Point2f tl(vertices[1]);
        tl.x -= 80;
        tl.y -= 7;
        Point2f bt(vertices[3]);
        bt.x += 15;
        bt.y += 10;

        // Draw contours
        // rectangle(frame, tl, bt,Scalar(0, 255, 0), 3 );

        // To calculate ROI we take one of vertices of a rectangle
        // calculate the width and height of ROI we want.
        // To calculate width and height of ROI we use remaining vertices.
        // Usually, we have many boxes defined by EAST. We just want the
        // box containg license plate number. This box is always the largest box
        // Therefore, we need to determine the largest box first before calculating ROI.
        int area, w, h;
        w = bt.x - tl.x;
        h = bt.y - tl.y;
        area = w*h;
        if(area > maxArea){
            maxArea = area;
            verROI = tl;
            wid = w;
            hei = h;
        }
    }

    // Rect will return a rectangle of interest based on points detected by EAST algorithm  
    rect = Rect(verROI.x, verROI.y, wid, hei);
    roiImg = frame(rect);
    imwrite("roi.png", roiImg);

    // Set up Tesseract API
    char *outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Change tesseract mode to read a single line of text
    api->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
    Pix *image = pixRead("roi.png");
    api->SetImage(image);
    // Extract text from the image
    outText = api->GetUTF8Text();
    outText[strlen(outText) - 1] = '\0';
    std::string ret = outText;
    delete api;
    delete [] outText;
    pixDestroy(&image);
    return ret;
}

void LicensePlateScanner::decode(const Mat& scores, const Mat& geometry, float scoreThresh,
            std::vector<RotatedRect>& detections, std::vector<float>& confidences) {
    detections.clear();
    CV_Assert(scores.dims == 4); CV_Assert(geometry.dims == 4); CV_Assert(scores.size[0] == 1);
    CV_Assert(geometry.size[0] == 1); CV_Assert(scores.size[1] == 1); CV_Assert(geometry.size[1] == 5);
    CV_Assert(scores.size[2] == geometry.size[2]); CV_Assert(scores.size[3] == geometry.size[3]);

    const int height = scores.size[2];
    const int width = scores.size[3];
    for (int y = 0; y < height; ++y)
    {
        const float* scoresData = scores.ptr<float>(0, 0, y);
        const float* x0_data = geometry.ptr<float>(0, 0, y);
        const float* x1_data = geometry.ptr<float>(0, 1, y);
        const float* x2_data = geometry.ptr<float>(0, 2, y);
        const float* x3_data = geometry.ptr<float>(0, 3, y);
        const float* anglesData = geometry.ptr<float>(0, 4, y);
        for (int x = 0; x < width; ++x)
        {
            float score = scoresData[x];
            if (score < scoreThresh)
                continue;

            // Decode a prediction.
            // Multiple by 4 because feature maps are 4 time less than input image.
            float offsetX = x * 4.0f, offsetY = y * 4.0f;
            float angle = anglesData[x];
            float cosA = std::cos(angle);
            float sinA = std::sin(angle);
            float h = x0_data[x] + x2_data[x];
            float w = x1_data[x] + x3_data[x];

            Point2f offset(offsetX + cosA * x1_data[x] + sinA * x2_data[x],
                           offsetY - sinA * x1_data[x] + cosA * x2_data[x]);
            Point2f p1 = Point2f(-sinA * h, -cosA * h) + offset;
            Point2f p3 = Point2f(-cosA * w, sinA * w) + offset;
            RotatedRect r(0.5f * (p1 + p3), Size2f(w, h), -angle * 180.0f / (float)CV_PI);
            detections.push_back(r);
            confidences.push_back(score);
        }
    }
}

