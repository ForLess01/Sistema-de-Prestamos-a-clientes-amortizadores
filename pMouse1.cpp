#include "gMouse.h"
#include <graphics.h>
#include <stdio.h>

void main(){
	cMouse objMouse; // objeto para el manejo del mouse
	cleardevice();
	if (!objMouse.mNumBotones()){
		outtext("su computador no tiene MOUSE ... presione ENTER ");
		getch();
	}
	else{
		char cadena [256] ;
		sprintf(cadena,
				"su mouse tiene %3d Botones",objMouse.mNumBotones());
		outtextxy(100, 100,cadena);
		outtextxy(100, 130, "presione un boton del mouse o trasladelo ... ");
		objMouse.Muestra();

		objMouse.Utiliza();
		objMouse.Resultados();

		outtextxy(100, 160, "presione un boton del mouse o traslade/o ... ");
		objMouse.GotoXY(70 * 8, 15 * 8); // mueve el mouse a columna 70,flla 15
		objMouse.Muestra();

		objMouse.Utiliza();
		objMouse.Resultados();
	}
}
