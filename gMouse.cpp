#include "gMouse.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
// -----------------------------------------------------------------------
cMouse::cMouse(char* pvRuta)
{
	NumBotones = Inicializa();
	int drive, modo, error;
	detectgraph(&drive, &modo);
	initgraph(&drive, &modo, pvRuta);
	error = graphresult();
	if (error != grOk){
		cout << "error. no encuentro ruta de librería grajica";
		getch();
		exit(I);
	}
}

cMouse :: ~cMouse()
{
	if (NumBotones)
	{
		Inicializa();
		closegraph();
	}
}

int cMouse :: Inicializa(){
	registro.X.ax = 0;
	int86(0x33, &registro, &registro);
	return registro.x.bx;
}

void cMouse::Muestra(){
	registro.x.ax = 1;
	int86(0x33, &registro, &registro);
}

void cMouse::Esconde(){
	registro.X.ax = 2;
	int86(0x33, &registro, &registro);
}

void cMouse::Estado(){
	registro.X.ax = 3;
	int86(0x33, &registro, &registro);
	BotonPulsado = registro.x.bx;
	Columna = registro.x.cx; // columna en pixels
	Fila = registro.x.dx; // fila en pixel
}

void cMouse::GotoXY(unsigned int X, unsigned int Y){
	registro.X.ax = 4;
	registro.x.cx = X; // columna en pixels
	registro.x.dx = Y; // fila en pixels
	int86(0x33, &registro, &registro);
}

void cMouse::Utiliza()
{
	do {
		Estado();
	} while (!BotonPulsado);
}

void cMouse::Resultados(){
	char cadena[ 256 ];
	switch (BotonPulsado) {
	case 1: outtextxy(100, 430, "pulso el boton izquierdo "); break;
	case 2: outtextxy(100, 430, "pulso el boton derecho "); break;
	case 4: outtextxy(100, 430, "pulso el boton del centro"); break;
	}
	sprintf(cadena,
			"en las coordenadas: columna %4d, fila %4d. Presione ENTER",
			Columna, Fila);
	outtextxy(100,460,cadena);
	getch();
	cleardevice();
}







