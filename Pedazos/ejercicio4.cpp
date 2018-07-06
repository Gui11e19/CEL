#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//espacio entre los bordes de la ventana y nuestra cuadricula
#define espacio 10
//tamano de cada espacio de la cuadricula
#define tam 50
//dimensiones de la cuadricula
#define filas 3
#define columnas 3

int matriz[filas][columnas];
Scalar negro(0, 0, 0);
Scalar blanco(255, 255, 255);
//para indicar si se ha presionado dentro de la cuadricula
bool bandera = false;
//para indicar si se ha encontrado un jugador
bool juegoTermino = false;

int altoV = tam*columnas + espacio * 2;
int anchoV = tam * filas + espacio * 2;
Mat ventana(altoV, anchoV, CV_8UC3, negro);

void dibujarMatriz() {
	//dibujar bordes horizontales
	for (int i = 0; i < filas + 1; i++)
	{
		Point inicio1(espacio, tam * i + espacio);
		Point fin1(tam*columnas + espacio, tam * i + espacio);
		line(ventana, inicio1, fin1, blanco);
	}
	//dibujar bordes verticales
	for (int i = 0; i < filas + 1; i++)
	{
		Point inicio2(tam * i + espacio, espacio);
		Point fin2(tam * i + espacio, tam*filas + espacio);
		line(ventana, inicio2, fin2, blanco);
	}
}

void dibujarEquis(int x, int y) {
	Point inicio1(x + espacio, y + espacio);
	Point fin1(x + tam - espacio, y + tam - espacio);
	line(ventana, inicio1, fin1, blanco);

	Point inicio2(x + tam - espacio, y + espacio);
	Point fin2(x + espacio, y + tam - espacio);
	line(ventana, inicio2, fin2, blanco);
}

void dibujarCero(int x, int y) {
	Point centro(x + tam / 2, y + tam / 2);
	int radio = tam / 2 - espacio;
	circle(ventana, centro, radio, blanco);
}

void dibujarGanador(int num) {
	Mat ventana2(100, 300, CV_8UC3, negro);
	string texto = (num == 1) ? "X" : "0";
	putText(ventana2, "Ganador: " + texto, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, blanco);
	imshow("Ganador", ventana2);

	juegoTermino = true;
}

void dibujarEmpate() {
	Mat ventana2(100, 300, CV_8UC3, negro);
	putText(ventana2, "-Empate-", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, blanco);
	imshow("Empate", ventana2);

	juegoTermino = true;
}

void verificarGanador() {
	//revisar horizontalmente
	for (int i = 0; i < filas; i++)
		if (matriz[i][0] == matriz[i][1] &&
			matriz[i][0] == matriz[i][2] &&
			matriz[i][0] != 0) dibujarGanador(matriz[i][0]);

	//revisar verticalmente
	for (int i = 0; i < columnas; i++)
		if (matriz[0][i] == matriz[1][i] &&
			matriz[0][i] == matriz[2][i] &&
			matriz[0][i] != 0) dibujarGanador(matriz[0][i]);

	//revisar diagonalmente
	if (matriz[0][0] == matriz[1][1] &&
		matriz[0][0] == matriz[2][2] &&
		matriz[0][0] != 0) dibujarGanador(matriz[0][0]);

	if (matriz[2][0] == matriz[1][1] &&
		matriz[2][0] == matriz[0][2] &&
		matriz[2][0] != 0) dibujarGanador(matriz[2][0]);
}

void verificarEmpate() {
	int casillasOcupadas = 0;

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++)
			if (matriz[i][j] != 0) casillasOcupadas++;

	if (!juegoTermino && casillasOcupadas == 9) dibujarEmpate();
}

void onMouse(int event, int x, int y, int, void*) {
	if (juegoTermino) return;

	if (event == EVENT_LBUTTONUP)
		for (int i = 0; i < filas; i++)		
			for (int j = 0; j < columnas; j++)
			{
				int valorX = tam*i + espacio;
				int valorY = tam*j + espacio;

				if (x >= valorX && x < valorX + tam &&
					y >= valorY && y < valorY + tam && matriz[i][j] == 0) {

					matriz[i][j] = (bandera ? 1 : 2);

					x = tam * ((x - espacio) / tam) + espacio;
					y = tam * ((y - espacio) / tam) + espacio;

					bandera ? dibujarEquis(x, y) : dibujarCero(x, y);
					bandera = !bandera;

					verificarGanador();
					verificarEmpate();
				}
			}
}

int main()
{
	namedWindow("Ventana");
	setMouseCallback("Ventana", onMouse);

	dibujarMatriz();

	while (true)
	{
		imshow("Ventana", ventana);
		if (waitKey(10) == 27) break;
	}
	return 0;
}
