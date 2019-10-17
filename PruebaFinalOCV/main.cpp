#include <opencv2\highgui\highgui.hpp>
//Libreria para procesar la imagen, cambiar el color, recortar, etc.
#include <opencv2\imgproc\imgproc.hpp>
//Libreria que detecta objetos en imagenes
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "FaceDetector.h"

using namespace std;
using namespace cv;

//Se inicializa el nextFrame
void nextFrame(Mat frame);

//ubicacion de archivos para que el algoritmo sepa que es una cara
string face_cascade_name = "C:\\OpenCV-4.1.1\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";

//Nombre de la ventana
string window_name = "Deteccion Facial";
//Tamaño inicial pequeño para mejorar eficiencia
int next_height = 40;

int main(int argc, const char **argv)
{
        //Variables de captura de imagen y matriz de valores donde se guardara esta captura
        VideoCapture capture;
        Mat frame;
        vector<Rect> faces;

        //llamar a la clase
        FaceDetector Detect(face_cascade_name, next_height);

        //Se asigna video en vivo a captura
        capture = VideoCapture(0);

        //@ Si existe captura...
        if (capture.isOpened())
        {
                while (true)
                {
                        capture >> frame;
                        //@ Si la matriz no se encuentra vacia...
                        if (!frame.empty())
                        {
                                //funcion de detectar
                                faces = Detect.nextFrame(frame);
                        }
                        else
                        {
                                //La matriz esta vacia, marcar error
                                printf("Error: No existe un frame capturado");
                                break;
                        }

                        //Hacer print a las coordenadas.

                        cout << "########################################" << endl;

                        for (int i = 0; i < faces.size(); i++)
                        {
                                cout << i << ": "
                                     << "(" << faces[i].x << "," << faces[i].y << ")" << endl;
                        }

                        cout << "#########################################" << endl;

                        //    //mostrar video en vivo con lo que se obtuvo
                        //imshow( window_name, frame );
                }
        }

		//La siguiente sección es para que se pueda probar con una librería de fotos

        /*
        string test = "D:\\Fotos de Viajes\\2017\\Junio-Diciembre\\100ANDRO (1)\\DSC_0023.JPG";

        faces = Detect.ImgDetect(test);

        cout << "########################################" << endl;

        for (int i = 0; i < faces.size(); i++)
        {
                cout << i << ": "
                     << "(" << faces[i].x << "," << faces[i].y << ")" << endl;
        }

        cout << "#########################################" << endl;

        char r = getchar();

        */

        return 0;
}
