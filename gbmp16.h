#if !defined _gBMP16_h_
#define _gBMP16_h_
#include <fstream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

// definición de la estructura
struct sBMP {
	unsigned NumCol, NumFilas;
	unsigned char** Mapa;
};

// definición de la clase
class cBMP16{
private:
	char NombreBMP[81];
	char Ruta[81];
	sBMP RegBMP;

public:
	cBMP16(char* pbmp = "c:\\windows\\zigzag.bmp",
			char* pruta = "c:\\borlandc\\bgi");
	~cBMP16();
	void IniciaGrafico();
	void LeeBitMap();
	void DibujaBitMap(unsigned xSupIzq, unsigned ySupIzq);
	void PresentaBMP();
};
#endif