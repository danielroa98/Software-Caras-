
#ifndef FaceDetector_hpp
#define FaceDetector_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

class FaceDetector
{
private:
cv::CascadeClassifier face_cascade;
int next_height;
public:
FaceDetector(std::string face_cascade_name, int next_height_ = 40);
FaceDetector();
~FaceDetector() 
{
};
std::vector<cv::Rect> nextFrame (cv::Mat frame);
std::vector<cv::Rect> ImgDetect  (string path);
};

#endif /* FaceDetector_hpp */
