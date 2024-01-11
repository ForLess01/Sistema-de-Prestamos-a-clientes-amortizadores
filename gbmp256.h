#if !defined _gBMP256_h_
#define _gBMP256_h_
// definición de la clase de bmps 256 colores
class cBMP256 {
private:
	char filename[121];
	char ruta[121];
	int columna, fila;
public:
	cBMP256(char* pfilename, int x = 0, int y = 0, char* pruta = "c:\\borlandc\\bgi");

private:
	int OPEN(unsigned char mode);
	int CREATE();
	void CLOSE(int handle);
	int READ(int handle, unsigned nbytes, void far *data);
	int WRITE(int liandle, unsigned nbytes, void far *data);
	long LSEEK(int handle, long nbytes, int whence);
	void Init_Graph(unsigned char Modo);
	void Close_Graph();
	void Putpixel_256(int fila, int columna, unsigned char color);
	void SET_BLOCK_DAC(void far *block_dac, int i, int ncolores);
	void SET_DAC_BLANK();
	void GET_HEADER_BMP(unsigned handle);
	void GET_DAC_BMP_256(int handle);
	void SET_BMP_256(unsigned handle);
	void ViewFull();
	void HideView();
public:
	void Draw();
};
#endif