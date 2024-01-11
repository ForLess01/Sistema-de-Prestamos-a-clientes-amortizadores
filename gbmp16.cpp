#include "gBMP16.h"
#include <string.h>


cBMP16 :: cBMP16(char* pbmp, char* pruta)
{
	strcpy(NombreBMP, pbmp);
	strcpy(Ruta, pruta);
	IniciaGrafico();
};

cBMP16 :: ~cBMP16(){
	unsigned PosY;
	for (PosY = 0; PosY < RegBMP.NumFilas; PosY++)
		delete (RegBMP.Mapa[PosY]);
	delete (RegBMP.Mapa);
	closegraph();
}

void cBMP16 ::IniciaGrafico(){
	int drive, modo, error;

	detectgraph(&drive, &modo);
	initgraph(&drive,&modo, Ruta);
	error = graphresult();
	if (error != grOk)
	exit(1);
}

void cBMP16::LeeBitMap()
{
	fstream ArchBitMap;
	unsigned long num;
	unsigned i;

	ArchBitMap.open(NombreBMP,ios::in\ios: : binary);
	if (!ArchBitMap)
		exit(1);

	ArchBitMap.seekg(18L, ios::beg);
	ArchBitMap.read((char*)&num, sizeof(unsigned long));
	RegBMP.NumCol = (unsigned)num;
	ArchBitMap.read((char*)&num, sizeof(unsigned long));
	RegBMP.NumFilas = (unsigned)num;
	ArchBitMap.seekg(118L, ios::beg);
	RegBMP.Mapa = (unsigned char**)
			new char[((RegBMP.NumFilas) * sizeof(unsigned char*))];
	for (i = 0L; i < RegBMP.NumFilas; i++){
		RegBMP.Mapa[i] = (unsigned char*)
				new char[(RegBMP.NumCol / 2 * sizeof(unsigned char))];
		ArchBitMap.read(RegBMP.Mapa[i], RegBMP.NumCol / 12);
	}
	ArchBitMap.close();
}

void cBMP16 :: DibujaBitMap(unsigned xSupIzq, unsigned ySupIzq) {
	unsigned fila, col;
	for (fila = 0; fila < RegBMP.NumFilas; fila++)
		for (col = 0; col < RegBMP.NumCol / 2; col++) {
			putpixel(xSupIzq + col * 2, ySupIzq + fila, RegBMP.Mapa[fila][col] >> 4);
			putpixel(xSupIzq + col * 2 + 1 , ySupIzq + fila, RegBMP.Mapa[fila][col] & 0x0F);
		}
}

void cBMP16 ::PresentaBMP() {
	unsigned PosX, PosY;
	LeeBitMap();
	for (PosY = 0; PosY < 15; PosY++)
		for (PosX = 0; PosX < 20; PosX++)
			DibujaBitMap(PosX * RegBMP.NumCol, PosY * RegBMP.NumFilas);
	getch();
}