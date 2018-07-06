#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

string frase = "";
Scalar negro(0, 0, 0);
Scalar blanco(255, 255, 255);
int contador = 0;

int main()
{
	while (true)
	{
		Mat ventana(100, 400, CV_8UC3, negro);

		putText(ventana, frase, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, blanco);

		imshow("Ventana", ventana);

		char tecla = waitKey(10);
		if(tecla == 27) break;

		if (tecla >= 'a' && tecla <= 'z' && contador < 20) {
			frase += tecla;
			contador++;
		}
	}
	return 0;
}
