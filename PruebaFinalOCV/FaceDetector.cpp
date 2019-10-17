#include "FaceDetector.h"
using namespace cv;
using namespace std;

//@ constructor requiere el path a los xml con los datos para el Cascade Classifier
FaceDetector::FaceDetector(std::string face_cascade_name, int next_height_)
{
        face_cascade.load(face_cascade_name);
        next_height = next_height_;
}

FaceDetector::FaceDetector()
{
        face_cascade.load("C:\\OpenCV-4.1.1\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml"); //Hay que hacer esto genericamente

        //Se pueden incluir otros xmls, dependiendo de como apareceran las caras, como haarcascade_frontalface_alt_tree o haarcascade_frontalface_alt2
        next_height = 40;
}

//# funcion detectar
vector<Rect> FaceDetector::nextFrame(Mat frame)
{
        //declarar arreglo de rectangulos donde se guardan las caras existentes en la matriz
        //declarar nueva matriz para grises

        vector<Rect> faces;
        Mat frame_gray;

        if (face_cascade.empty())
        {
                cout << "Cascade data file reference not found";
        }
        if (frame.empty())
        {
                cout << "No more frames";
        }

        //convertir la matriz a una matriz de escala de grises
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        //
        equalizeHist(frame_gray, frame_gray);

        //@ si la cara es menor a 40px se asignan 40px
        if (next_height < 40)
        {
                next_height = 40;
        }

        //Detectar caras (∆)
        //@ Params: frame en gris, vector de caras, factor de expansion de imagen, numero de pasadas por frame, ?, tamaño de busqueda si no se encuentra.
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 4, 0, Size(next_height, next_height));

        //@ Tamaño de primer cara en primer frame

        //@ for para remarcar cada cara detectada y guardada en el arreglo
        for (size_t i = 0; i < faces.size(); i++)
        {

                if (i == 0)
                {
                        next_height = faces[0].height;
                }

                //@ encuentra la cara mas pequeña existente
                if ((next_height > faces[i].height) && (i > 0))
                {
                        next_height = faces[i].height;
                }

                //obtener el 80% del tamaño de la imagen
                next_height = next_height * 0.8;
        }

        return faces;
}

vector<Rect> FaceDetector::ImgDetect(string path)
{
        Mat img = imread(path, IMREAD_UNCHANGED);
        vector<Rect> faces;
        if (img.empty())
        {
                cout << "No se encontro imagen";
                exit(0);
        }
        else
        {
                face_cascade.detectMultiScale(img, faces, 1.1, 4, 0, Size(next_height, next_height));
        }

        // imwrite(path, img);
        return faces;
}

/*
   ∆ = Se detectan las caras existentes en la matriz en escala de grises y las guarda en el
   arreglo de faces, para esto revisa la cara con un cuadro que va incrementando en 1.1 veces
   su tamaño y busca por caras 4 veces pro frame para tener mayor exactitud, para revisar la
   imagen se hacen matrices del 80% del tamaño de la cara mas pequeña detectada en el ultimo
   frame, si no se han detectado caras se revisa por un tamaño de 40x40 recorriendo ese valor
   por los cuadros existentes en la imagen.
 */
