#include<iostream>
#include<stdlib.h>

#include<opencv2\objdetect\objdetect.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\videoio\videoio.hpp>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	VideoCapture cap;
	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	if (!cap.open(0))
		return 0;
	for (;;)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty()) break; // end of video stream
		imshow("FaceDetection works", frame);
		if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
	}

	CascadeClassifier faceDetection;
	if (!faceDetection.load("C:\\OpenCV-4.1.1\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml"))
	{
		cout << "\nFile isn't loaded properly";
			exit(0);
	}
	/*
	char path[100];
	cout << "\nEnter the path to the image for face detection:";
	cin.getline(path, 100);
	*/

	//Mat img = imread(path, IMREAD_UNCHANGED);


	if (cap.isOpened()) {
		cout << "\nNo hay imagen";
	}
	else
	{
		cout << "\nSe encontró la foto\nProcesando";
	
		vector<Rect>faces;
		Mat frame;

		cap = VideoCapture(0);
		
		if (cap.isOpened())
		{
			cap >> frame;

			faceDetection.detectMultiScale(frame, faces);

			for (int i = 0; i < faces.size(); i++)
			{
				Point pt1(faces[i].x, faces[i].y);
				Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));

				rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
			}//fin for

			cout << "\nSe detectaron rostros";
		}


	}
	return 0;
}