/*
#include<iostream>
#include<stdlib.h>
#include<opencv2\objdetect\objdetect.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main() {

	CascadeClassifier faceDetection;
	if (!faceDetection.load("C:\\OpenCV-4.1.1\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml"))
	{
		cout << "\nFile isn't loaded properly";
		exit(0);
	}

	//cout << "\nEnter the path to the image for face detection:";
	//cin.getline(path, 100);

	char path[100] = "C:\\Users\\danie\\Pictures\\Hrvatska\\KRKA";

	Mat img = imread(path, IMREAD_UNCHANGED);

	if (img.empty()) {
		cout << "\nNo hay imagen";
	}
	else
	{
		cout << "\nSe encontró la foto\nProcesando";

		vector<Rect>faces;

		faceDetection.detectMultiScale(img, faces);

		for (int i = 0; i < faces.size(); i++)
		{
			Point pt1(faces[i].x, faces[i].y);
			Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));

			rectangle(img, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
		}//fin for

		cout << "Se imprimió la imagen" << imwrite("C:\\Users\\danie\\Pictures\\Hrvatska\\KRKA\\Demo1.jpg", img) << endl;

		cout << "\nSe detectaron rostros";
	}


	return 0;
}
*/