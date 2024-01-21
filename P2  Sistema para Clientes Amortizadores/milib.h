#if !defined _MILIB_H_
#define _MILIB_H_0

void EscribeCad(int columna, int fila, const char* cadena);
void EscribeFecha(int columna, int fila, int dia, int mes, int anio);
0
void CentraCad(int fila, const char*cadena);

char *RepiteCad(int longitud, char caracter);

void PintaFila(int fila, int colini, int colfin, char caracter);

void PintaCol(int col, int filaini, int filafin, char caracter);

void DibujaCuadrado(int col_ini, int fila_ini, int col_term, int fila_term,
                    const char * bordes = "++++-/");

void BorraCuadrado(int col_ini, int fila_ini, int col_term, int fila_term);

void BorraArea(int colini, int filaini, int colfin, int filafin);

int ValidaFecha(int dia, int mes, int anio);

unsigned char*IngresaCad(int columna, int fila, int longitud,
                         unsigned char atributo = 16+8+7);

int IngresaEnt(int columna, int fila, int longitud);

float IngresaReal(int columna, int fila, int longitud);
void IngresaFecha(int columna, int fila, int &dia, int &mes, int &anio);

void Mensaje(int fila, const char *texto);

char Respuesta(int fila, const char*pregunta, const char*respuestas);

char EnterOEsc(int fila, const char*pregunta="ENTER = continua, ESC = termina");

char *Extraer(const char*cadena, int inicio, int cantidad);

char*Insertar(const char*cadena1, const char*cadena2, int posicion);

char *Suprimir(const char*cadena, int posicion, int cantidad);

int PosCad(const char*cadena1, char*cadena2);

char *FormatoNum(float numero, int ndec=2);

unsigned char *MensajeSecreto(const char*mensaje);

unsigned char*AlineaDer(int longitud, char*cadena);

int MenuPopUp(int col, int fil, const char**TextoMenu, int NumOpciones,
              int ConMarco = 1, unsigned char Atributo=63+8+7);

int MenuBarra(int col, int fil, const char**TextoMenu, int NumOpciones,
              int espaciado=3, unsigned char Atributo=24+8+7);

void FechaSistema(int &DiaDeSem, int &Dia, int &Mes, int &Anio);

char *FormatoFecha(int d, int m, int a);

void gotoxy(int x, int y);

int wherex();

int wherey();

void clrscr();

void textattr(int color);

void textcolor(int color);

void textbackground(int color);

void window(int x, int y, int width, int heigth);

void clreol();

int random(int min, int max);

void _setcursortype(bool visible);

void delay(int miliseconds);

#endif
