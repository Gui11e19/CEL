
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//espacio entre los bordes de la ventana y nuestra cuadricula
#define espacio 150
//tamano de cada espacio de la cuadricula
#define tam 50
//dimensiones de la cuadricula
#define filas 8
#define columnas 8
//700x700
int matriz[filas][columnas];
Scalar negro(0, 0, 0), blanco(255, 255, 255), azul(255,0,0), rojo(0, 0, 255), gris(128,128,128);

//para indicar si se ha presionado dentro de la cuadricula
bool bandera = false;
//para indicar si se ha encontrado un jugador
bool juegoTermino = false;

int altoV = tam * columnas + espacio * 2;
int anchoV = (tam * filas + espacio * 2)+80;
Mat ventana(altoV, anchoV, CV_8UC3, negro);

/*void ventanaMenu() {
	Mat ventanamenu(170, 280, CV_8UC3, Scalar(blanco));
	namedWindow("Menu.");


	
}
*/
void dibujarExtras() {
	//dibujar el fondo, titulo tablas, etc...
	Mat imgMadera = imread("madera1.jpg");
	imgMadera.copyTo(ventana(Rect(0, 0, imgMadera.cols, imgMadera.rows)));
	
	Point ptitulo(230, 80);
	float tamtit = 1.5;
	putText(ventana, "Connect 4 ", ptitulo, FONT_HERSHEY_DUPLEX, tamtit, negro);

	Mat imgMadera1 = imread("madera.jpg");
	imgMadera1.copyTo(ventana(Rect(600, 150, imgMadera1.cols, imgMadera1.rows)));

	//Rect marcon(600, 150, 150, 400); //contorno del marcador
	//rectangle(ventana, marcon, Scalar(gris), CV_FILLED);
	
	Point in1(600, 190); //in1 y fi1 es linea horizontal del marcador
	Point fi1(748, 190);
	line(ventana, in1, fi1, Scalar(blanco));

	Point in2(650, 190); //in2 y fi2 es linea vertical del marcador
	Point fi2(650, 550);
	line(ventana, in2, fi2, Scalar(blanco));

}

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

void dibujarFazul(int x, int y) {
	Point centro1(x + tam/2, y + tam/2);
	circle(ventana, centro1, 22, azul, CV_FILLED);
}

void dibujarFroja(int x, int y) {
	Point centro2(x + tam / 2, y + tam / 2);
	int radio = tam / 2 - espacio;
	circle(ventana, centro2, 22, rojo, CV_FILLED);
}

void dibujarGanador(int num) {
	Mat ventana2(100, 400, CV_8UC3, negro);
	string texto = (num == 1) ? "J1 azul" : "J2 rojo";
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
	//revisar vertical
	for (int i = 0; i < filas; i++)
		if (matriz[i][0] == matriz[i][1] &&
			matriz[i][0] == matriz[i][2] &&
			matriz[i][0] == matriz[i][3] &&
			matriz[i][0] != 0 ||
			matriz[i][1] == matriz[i][2] &&
			matriz[i][1] == matriz[i][3] &&
			matriz[i][1] == matriz[i][4] &&
			matriz[i][1] != 0 ||
			matriz[i][2] == matriz[i][3] &&
			matriz[i][2] == matriz[i][4] &&
			matriz[i][2] == matriz[i][5] &&
			matriz[i][2] != 0 ||
			matriz[i][3] == matriz[i][4] &&
			matriz[i][3] == matriz[i][5] &&
			matriz[i][3] == matriz[i][6] &&
			matriz[i][3] != 0 ||
			matriz[i][4] == matriz[i][5] &&
			matriz[i][4] == matriz[i][6] &&
			matriz[i][4] == matriz[i][7] &&
			matriz[i][4] != 0 ||
			matriz[i][5] == matriz[i][6] &&
			matriz[i][5] == matriz[i][7] &&
			matriz[i][5] == matriz[i][8] &&
			matriz[i][5] != 0
			) dibujarGanador(matriz[i][0]);

	//revisar horizontal
	for (int i = 0; i < columnas; i++)
		if (matriz[0][i] == matriz[1][i] &&
			matriz[0][i] == matriz[2][i] &&
			matriz[0][i] == matriz[3][i] &&
			matriz[0][i] != 0 ||
			matriz[1][i] == matriz[2][i] &&
			matriz[1][i] == matriz[3][i] &&
			matriz[1][i] == matriz[4][i] &&
			matriz[1][i] != 0 ||
			matriz[2][i] == matriz[3][i] &&
			matriz[2][i] == matriz[4][i] &&
			matriz[2][i] == matriz[5][i] &&
			matriz[2][i] != 0 ||
			matriz[3][i] == matriz[4][i] &&
			matriz[3][i] == matriz[5][i] &&
			matriz[3][i] == matriz[6][i] &&
			matriz[3][i] != 0 ||
			matriz[4][i] == matriz[5][i] &&
			matriz[4][i] == matriz[6][i] &&
			matriz[4][i] == matriz[7][i] &&
			matriz[4][i] != 0 ||
			matriz[5][i] == matriz[6][i] &&
			matriz[5][i] == matriz[7][i] &&
			matriz[5][i] == matriz[8][i] &&
			matriz[5][i] != 0) dibujarGanador(matriz[0][i]);

	//revisar diagonalmente
	if (matriz[0][0] == matriz[1][1] &&
		matriz[0][0] == matriz[2][2] &&
		matriz[0][0] == matriz[3][3] &&
		matriz[0][0] != 0 ||
		matriz[1][1] == matriz[2][2] &&
		matriz[1][1] == matriz[3][3] &&
		matriz[1][1] == matriz[4][4] &&
		matriz[1][1] != 0 || 
		matriz[2][2] == matriz[3][3] &&
		matriz[2][2] == matriz[4][4] &&
		matriz[2][2] == matriz[5][5] &&
		matriz[2][2] != 0 || 
		matriz[3][3] == matriz[4][4] &&
		matriz[3][3] == matriz[5][5] &&
		matriz[3][3] == matriz[6][6] &&
		matriz[3][3] != 0 || 
		matriz[4][4] == matriz[5][5] &&
		matriz[4][4] == matriz[6][6] &&
		matriz[4][4] == matriz[7][7] &&
		matriz[4][4] != 0 || 
		matriz[5][5] == matriz[6][6] &&
		matriz[5][5] == matriz[7][7] &&
		matriz[5][5] == matriz[8][8] &&
		matriz[5][5] != 0
		) dibujarGanador(matriz[0][0]);

	if (matriz[0][7] == matriz[1][6] &&
		matriz[0][7] == matriz[2][5] &&
		matriz[0][7] == matriz[3][4] &&
		matriz[0][7] != 0 ||
		matriz[0][6] == matriz[1][5] &&
		matriz[0][6] == matriz[2][4] &&
		matriz[0][6] == matriz[3][3] &&
		matriz[0][6] != 0 ||
		matriz[0][5] == matriz[1][4] &&
		matriz[0][5] == matriz[3][3] &&
		matriz[0][5] == matriz[3][2] &&
		matriz[0][5] != 0 ||
		matriz[0][4] == matriz[1][3] &&
		matriz[0][4] == matriz[2][2] &&
		matriz[0][4] == matriz[3][1] &&
		matriz[0][4] != 0 ||
		matriz[0][3] == matriz[1][2] &&
		matriz[0][3] == matriz[2][1] &&
		matriz[0][3] == matriz[3][0] &&
		matriz[0][3] != 0 
		) dibujarGanador(matriz[2][0]);
		
}


void verificarEmpate() {
	int casillasOcupadas = 0;

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++)
			if (matriz[i][j] != 0) casillasOcupadas++;

	if (!juegoTermino && casillasOcupadas == 64) dibujarEmpate();
}

void onMouse(int event, int x, int y, int, void*) {
	if (juegoTermino) return;

	if (event == EVENT_LBUTTONUP)
		for (int i = 0; i < filas; i++)
			for (int j = 0; j < columnas; j++)
			{
				int valorX = tam * i + espacio;
				int valorY = tam * j + espacio;

				if (x >= valorX && x < valorX + tam &&
					y >= valorY && y < valorY + tam && matriz[i][j] == 0) {

					matriz[i][j] = (bandera ? 1 : 2);

					x = tam * ((x - espacio) / tam) + espacio;
					y = tam * ((y - espacio) / tam) + espacio;

					bandera ? dibujarFazul(x, y) : dibujarFroja(x, y);
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
	//ventanaMenu();
	dibujarExtras();
	dibujarMatriz();

	while (true)
	{
		imshow("Ventana", ventana);
		if (waitKey(10) == 27) break;
	}
	return 0;
}
