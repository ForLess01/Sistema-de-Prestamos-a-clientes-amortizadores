#include "gMouse.h" // para la clase cMouse
#include "gBMP256.h" // para la clase cBMP256
#include <graphics.h>
#include <stdio.h>

void main()
{
	int salir = 0;
	do {
		cMouse objMouse; // objeto para el manejo del mouse
		objMouse.Muestra();

		cleardevice();
		setcolor(EGA_CYAN);
		outtextxy(150, 50, "PRESENTACION DE BMPS A 256 COLORES");

		setcolor(EGA_YELLOW);
		rectangle(90, 90, 200, 110); outtextxy(100, 100, "Las Dunas");
		rectangle(90, 120, 200, 140); outtextxy(100, 130, "Leon Bebe");
		rectangle(90, 150, 200, 170); outtextxy(100, 160, "Windows 95");
		rectangle(90, 180, 200, 200); outtextxy(100, 190, "Pamela Li ");

		setcolor(EGA_GREEN);
		rectangle(90, 230, 200, 250); outtextxy(100, 240, "Salir ");
		setcolor(EGA_WHITE);
		outtextxy(100, 450, "haga clik en alguna de las opciones");
		do {
			objMouse.Utiliza();
		} while (objMouse.mBotonPulsado() != 1);

		if (objMouse.mColumna() >= 90 && objMouse.mColumna() <= 200) {
			if (objMouse.mFila() >= 90 && objMouse.mFila() <= 110) {
				cBMP256 objDunas("dun.bmp");
				objDunas.Draw();
			}
			if (objMouse.mFila() >= 120 && objMouse.mFila() <= 140) {
				cBMP256 objLeon("le.bmp ");
				objLeon.Draw();
			}
			if (objMouse.mFila() >= 150 && objMouse.mFila() <= 170) {
				cBMP256 objWin("plu.bmp");
				objWin.Draw();
			}
			if (objMouse.mFila() >= 180 && objMouse.mFila() <= 200) {
				cBMP256 objWin("pamela.bmp");
				objWin.Draw();
			}
			if (objMouse.mFila() >= 230 && objMouse.mFila() <= 250)
				salir = 1;
		}
	} while (!salir);
}
		