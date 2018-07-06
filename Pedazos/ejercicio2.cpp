/////////////////////////// Movimiento de cuadro /////////////////////////////////////////////
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int posX = 50, posY = 50;
Scalar negro(0, 0, 0);
Scalar blanco(255, 255, 255);

int main()
{
	while (true)
	{
		Mat ventana(150, 400, CV_8UC3, negro);

		Rect cuadro(posX, posY, 50, 50);
		rectangle(ventana, cuadro, blanco);

		if (posX < 300) {
			posX++;
			//este número dicta la velocidad del movimiento
			waitKey(10);
		}

		imshow("Ventana", ventana);
		if (waitKey(10) == 27) break;
	}
	return 0;
}

