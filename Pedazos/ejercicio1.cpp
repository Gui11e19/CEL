#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//espacio entre los bordes de la ventana y nuestra cuadricula
#define espacio 10
//dimensiones de cada espacio de la cuadricula
#define tam 50
//cantidad de filas de la cuadricula
#define filas 6

int arreglo[filas];
Scalar negro(0, 0, 0);
Scalar blanco(255, 255, 255);
//para indicar si se ha presionado dentro de la cuadricula
bool bandera = false;

void dibujarMatriz(Mat ventana) {
	//dibujar borde horizontal superior
	Point inicio1(espacio, espacio);
	Point fin1(tam * filas + espacio, espacio);
	line(ventana, inicio1, fin1, blanco);

	//dibujar borde horizontal inferior
	Point inicio2(espacio, tam + espacio);
	Point fin2(tam * filas + espacio, tam + espacio);
	line(ventana, inicio2, fin2, blanco);

	//dibujar bordes verticales
	for (int i = 0; i < filas + 1; i++)
	{
		Point inicio3(tam * i + espacio, espacio);
		Point fin3(tam * i + espacio, tam + espacio);
		line(ventana, inicio3, fin3, blanco);
	}
}

void mostrarArreglo() {
	for (int i = 0; i < filas; i++)
		cout << "| " << arreglo[i] << "\t";

	cout << "|" << endl;
}

void onMouse(int event, int x, int y, int, void*) {
	if (event == EVENT_LBUTTONUP) {
		for (int i = 0; i < filas; i++)
		{
			int valor = tam*i + espacio;
			if (x >= valor && x < valor + tam && y >= espacio && y <=tam + espacio) {
				arreglo[i]++;
				bandera = true;
			}
		}

		if (bandera) {
			mostrarArreglo();
			bandera = false;
		}
	}
}

int main()
{
	//inicializar la matriz con 0's al principio
	for (int i = 0; i < filas; i++) arreglo[i] = 0;

	while (true)
	{
		int altoV = tam + espacio * 2;
		int anchoV = tam * filas + espacio * 2;
		Mat ventana(altoV, anchoV, CV_8UC3, negro);
		namedWindow("Ventana");
		setMouseCallback("Ventana", onMouse);

		dibujarMatriz(ventana);

		imshow("Ventana", ventana);
		if (waitKey(10) == 27) break;
	}
	return 0;
}

