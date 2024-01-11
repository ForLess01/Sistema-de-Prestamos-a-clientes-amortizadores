#if !defined _gMouse_h_
#define _gMouse_h_
#include <iostream.h>
#include <conio.h>
#include <dos.h>
// definición de la clase
class cMouse {
private:
	union REGS registro;
	unsigned int NumBotones, BotonPulsado, Columna, Fila;
public:
	cMouse(char* pvRuta = "c:\\borlandc\\bgi");
	~cMouse();
	int Inicializa();
	void Muestra();
	void Esconde();
	void Utiliza();
	virtual void Estado();
	virtual void GotoXY(unsigned int X, unsigned int Y);
	virtual void Resultados();
	unsigned int mNumBotones() { return NumBotones; }
	unsigned int mBotonPulsado() { return BotonPulsado; }
	unsigned int mColumna() { return Columna; }
	unsigned int mFila() { return Fila; }
};
#endif 