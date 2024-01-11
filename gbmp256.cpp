#include <iostream.h>
#include <graphics.h>
#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <dos.h>
#include <fstream.b>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

#include "gbmp256.h"

struct REGPACK pack;
union REGS entrada, salida;

#define O_READ 0
#define O_WRITE 1
#define O_RDWR 2
typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;
/*---------------------------------------------------------------------*/

//definición de la cabecera de BMP's de 256 colores
struct HEADER_BMP {
	WORD bildentificacion;
	DWORD biSizeFile; /* sizefile=(tamaño del archivo)/2 */	
	WORD biReserv1;
	WORD biReserv2;
	DWORD biOffset;

	DWORD biSize;
	DWORD biWidth;
	DWORD biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;

	DWORD biSizelmage;
	DWORD biXpelspermeter;
	DWORD biYpelspermeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}bmp_h;

// definición de la estructura de colores de un bmp
struct DAC_BMP {
	unsigned char azul;
	unsigned char verde;
	unsigned char rojo;
	unsigned char reservado;
}bmp_d[256];

struct DAC_DOS {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
struct DAC_DOS DAC[256];
/*---------------------------------------------------------------------*/
//VARIABLES GWBALES
unsigned char modo, PATH[80];
unsigned char far* video = (unsigned char far*)0xA0000000L;
unsigned char far* font;
unsigned char sizefont = 8;
/*---------------------------------------------------------------------*/
cBMP256::cBMP256(char* pfilename, int x, int y, char* pruta){
	strcpy(filename, pfilename);
	strcpy(ruta, pruta);
	columna = x;
	fila = y;
}
/*---------------------------------------------------------------------*/
int cBMP256::OPEN(unsigned char mode){
	pack.r_ax = 0x3D00 + mode;
	pack.r_ds = FP_SEG(filename);
	pack.r_dx = FP_OFF(filename);
	intr(0x21, &pack);
	return(((pack.r_flags & 1) == 1) ?~pack.r_ax : pack.r_ax); //?? -pack.r_ax   o  ~pack.r_ax
}
/*-------------------------------------------------------streams .h-----*/

int cBMP256::CREATE() {
	pack.r_ax = 0x3C00; //datos
	pack.r_ex = 0x20; //contador
	pack.r_ds = FP_SEG(filename); //segmento
	pack.r_dx = FP_OFF(filename); 1 // direccion(area de datos extra)
	intr(0x21, &pack);
	retum(((pack.r_flags & 1) == 1) ? ~pack.r_ax : pack.r_ax);//?? -pack.r_ax   o  ~pack.r_ax
}
/*-................................................................... */
void cBMP256::CLOSE(int handle){
	pack.r_ax = 0x3E00;
	pack.r_bx = handle;
	intr(0x21, &pack); //tal vez sea asi ---> int r(0x21, &pack);
}
/* .................................................................... */

int cBMP256::READ(int handle, unsigned nbytes, void far* data) {
	pack.r_ax = 0x3F00;
	pack.r_bx = handle;
	pack.r_ex = nbytes;
	pack.r_ds = FP_SEG(data);
	pack.r_dx = FP_OFF(data);
	intr(0x21, &pack); //tal vez sea asi ---> int r(0x21, &pack);
	return (((pack.r_flags & 1) == 1) ? ~pack.r_ax : pack.r_ax); //?? -pack.r_ax   o  ~pack.r_ax
}
/* .................................................................... */
int cBMP256::WRITE(int handle, unsigned nbytes, void far* data) {
	pack.r_ax = 0x4000;
	pack.r_bx = handle;
	pack.r_cx = nbytes;
	pack.r_ds = FP_SEG(data);
	pack.r_dx = FP_OFF(data);
	intr(0x21, &pack);
	return (((pack.r_flags & 1) == 1) ? ~pack.r_ax : pack.r_ax);//?? -pack.r_ax   o  ~pack.r_ax
}
/* -·············· .............················· ..............·········· */
long cBMP256::LSEEK(int handle, long nbytes, int whence) {
	pack.r_ax = 0x4200 + whence;
	pack.r_bx = handle;
	pack.r_ex = (int)(nbytes / 65536L);
	pack.r_dx = (int)(nbytes % 65536L);
	intr(0x21, &pack);
	return (pack.r_dx * 65536L + pack.r_ax);
}
/* .......................... •·························· graphies. /¡ ••••• */

void cBMP256::Init_Graph(unsigned char Modo) {
	entrada.h.ah = 0; //desagrega al ax
	entrada.h.al = Modo; // ¡¡
	int86(0x10, &entrada, &salida);
}
/* •·· .......................... ....................................... */
void cBMP256::Close_Graph(void){
	Init_Graph(0x03);
}
/* •·· .......................... ....................................... */
void cBMP256::Putpixel_256(int fila, int columna, unsigned char color){
	video[fila * 320 + columna ] = color;
}
/*---... -----------. --. -.. -. ------. --.• -• --------• -• ---------••• -------*/
void cBMP256::SET_BLOCK_DAC(void far *block_dac, int i, int ncolores){
	pack.r_ax = 0x1012;
	pack.r_bx = i;
	pack.r_cx = ncolores;
	pack.r_es = FP_SEG(block_dac);
	pack.r_dx = FP_OFF(block_dac);
	intr(0x10, &pack);
}
/*-· ----. -. -. ------------.. ··-------------------• -----• ------• ----•••• -*/
void cBMP256::SET_DAC_BLANK(void){
	int i;
	unsigned char BLANK[ 768 ];
	for (i = 0; i < 768; i++) BLANK[i]= 0;
	SET_BLOCK_DAC(BLANK,0, 256); //?
}
/*-----. --. --------.. ------••• ---------------------··---------·-•• ----. */
void cBMP256::GET_HEADER_BMP(unsigned handle){
	READ(handle, sizeof(struct HEADER_BMP), &bmp_h);
}
/*-----. --. --------.. ------••• ---------------------··---------·-•• ----. */
void cBMP256 :: GET_DAC_BMP_256(int handle){
	int i;
	READ( handle, 1024,&bmp_d);
	for(i=0; i<256; i++){
		DAC[i].R = bmp_d[i].rojo >> 2;
		DAC[i].G = bmp_d[i].verde >> 2;
		DAC[i].B = bmp_d[i].azul >> 2;	
	}
}
/*--------. --------------------------------• -• -------•• -• ------••• -----*/

void cBMP256::SET_BMP_256(unsigned handle){
	unsigned char data[640];
	unsigned f, c, i;
	unsigned altura,ancho;
	altura = (bmp_h.biHeight > 199) ? 199 : (unsigned)bmp_h.biHeight;
	ancho = (unsigned)((bmp_h.biSizeFile-bmp_h.biOffset) / bmp_h.biHeight);
	LSEEK(handle, bmp_h.biOffset, 0);
	for (f = altura; f > 0; f--) {
		READ(handle, ancho, data);
		for (c = 0, i = 0; c < bmp_h.biWidth; i++, c++)
			Putpixel_256(fila + f,columna + c, data[i]);
	}
}
/*---------------------------------------·-----------------------------*/
void cBMP256::ViewFull() {
	int i, j;
	struct DAC_DOS far* p;
	struct DAC_DOS DAC1[256];
	movedata(FP_SEG(DAC), FP_OFF(DAC), FP_SEG(DACI), FP_OFF(DACI), 768);
	for (j = 0, j < 64, j++) {
		for (i = 0; i < 256; i++) {
			DACI[i].R = (j < DAC[i].R) ? j : DAC[i].R;
			DACI[i].G = (j < DAC[i].G) ? j : DAC[i].G;
			DACI[i].B = (j < DAC[i].B) ? j : DAC[i].B;
		}
		p = DACI;
		for (i = 0; i < 256; i += 128) {
			SET_BLOCK_DAC(p, i, 128);
			p += 128;
		}
	}
}
/*---------------------------------------------------------------------*/
void cBMP256::HideView() {
	int i, j;
	struct DAC_DOS far* p;
	struct DAC_DOS DACI[256];

	movedata(FP_SEG(DAC), FP_OFF(DAC), FP_SEG(DACI), FP_OFF(DACI), 768);
	for (j = 0; j < 64; j + +) {
		for (i = 0; i < 256; i++) {
			DACI[i].R -= 1;
			DACI[i].G -= 1;
			DACI[i].B -= 1;
		}
	}
}
/*----------------------------------------. ----------------------------*/
void cBMP256::Draw(){
	unsigned handle;
	handle = OPEN(O_READ);
	if (handle > 0) {
		LSEEK(handle, 0, 0);
		GET_HEADER_BMP(handle);
		GET_DAC_BMP_256(handle);
		if (bmp_h.biBitCount == 8) {
			Init_Graph(0x13);
			SET_DAC_BLANK();
			SET_BMP_256(handle);
			ViewFull();
			SET_BLOCK_DAC(DAC, 0, 256);
			getch();
			HideView();
		}
		else
			printf("\n No es formato de 256 colores");
		CLOSE(handle);
	}
	// Close_Graph( );
}
/*---------------------------------------------------------------------*/
