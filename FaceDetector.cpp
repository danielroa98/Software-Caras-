//OpenCV Libraries / Resources
#include<opencv2/core/core.hpp> //Basic structures of OpenCV (cv:: Mat, Scalar)
#include<opencv2/videoio/videoio.hpp> /*Video capturing from video files, image
sequences or cameras.*/
#include<opencv2/highgui/highgui.hpp>// OpenCV I/O Windows
#include<opencv2/imgproc/imgproc.hpp> //Gaussian Blur
#include<opencv2/objdetect/objdetect.hpp>//Cascade classifier class for object detection
//CascadeDetectorAdapter

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

const string WindowName = "Face Detection example";

class CascadeDetectorAdapter : public DetectionBasedTracker::IDetector
{
public:
	CascadeDetectorAdapter(cv::Ptr<cv::CascadeClassifier> detector) :
		IDetector(),
		Detector(detector)
	{
		CV_Assert(detector);
	}

	void detect(const cv::Mat& Image, std::vector<cv::Rect>& objects) CV_OVERRIDE
	{
		Detector->detectMultiScale(Image, objects, scaleFactor, minNeighbours, 0, minObjSize, maxObjSize);
	}

	virtual ~CascadeDetectorAdapter() CV_OVERRIDE
	{}

private:
	CascadeDetectorAdapter();
	cv::Ptr<cv::CascadeClassifier> Detector;
};



	std::string cascadeFrontalfilename = samples::findFile("data/lbpcascades/lbpcascade_frontalface.xml");
	cv::Ptr<cv::CascadeClassifier> cascade = makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);
	cv::Ptr<DetectionBasedTracker::IDetector> MainDetector = makePtr<CascadeDetectorAdapter>(cascade);

	//Error Handling ##############################################################################################
	if (cascade->empty())
	{
		printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
		return 2;
	}

	cascade = makePtr<cv::CascadeClassifier>(cascadeFrontalfilename);
	cv::Ptr<DetectionBasedTracker::IDetector> TrackingDetector = makePtr<CascadeDetectorAdapter>(cascade);
	if (cascade->empty())
	{
		printf("Error: Cannot load %s\n", cascadeFrontalfilename.c_str());
		return 2;
	}

	DetectionBasedTracker::Parameters params;
	DetectionBasedTracker Detector(MainDetector, TrackingDetector, params);

	if (!Detector.run())
	{
		printf("Error: Detector initialization failed\n");
		return 2;
	}

	//Error Handling ###############################################################################################

	Mat ReferenceFrame;
	Mat GrayFrame;
	vector<Rect> Faces;//Rect rec

	do
	{
		VideoStream >> ReferenceFrame;
		cvtColor(ReferenceFrame, GrayFrame, COLOR_BGR2GRAY); //Assumes as input a grayscale img.
															//We reduce processing form 3 (RGB) images to one.
		Detector.process(GrayFrame); //
		Detector.getObjects(Faces);

		for (size_t i = 0; i < Faces.size(); i++)
		{
			/*
			void cv::rectangle(InputOutputArray img,
				Rect 	rec,
				const Scalar & color,
				int 	thickness = 1,
				int 	lineType = LINE_8,
				int 	shift = 0
			)*/
			rectangle(ReferenceFrame, Faces[i], /Color/Scalar(0, 0, 255), /Thicc/3); //Devolver el rectangulo
		}

		imshow(WindowName, ReferenceFrame);
	} while (waitKey(30) < 0); //Espera a que presiona una tecla [esc] para terminar.

	Detector.stop();

	return 0;
}
