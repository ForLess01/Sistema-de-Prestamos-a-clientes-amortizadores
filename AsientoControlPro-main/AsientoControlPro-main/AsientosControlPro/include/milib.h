#ifndef MILIB_H
#define MILIB_H

/* escribir una cadena a partir de cualquier coordenada ( columna.fila) de la pantalla. */
void EscribeCad(int columna, int fila, const char *cadena);
void EscribeCad(int columna, int fila, const unsigned char *cadena);
/* escribir una fecha con e/formato dd/mes/aaaa a partir de cualquier coordenada de la
pantalla */
void EscribeFecha(int columna, int fila, int dia, int mes, int anio);
/* escribir una cadena centrada en cualquier fila de la pantalla. */
void CentraCad(int fila, const char *cadena);
/* devuelve una cadena compuesta de cierta cantidad de caracteres del mismo valor. Ejm
una cadena de 20 asteriscos; una cadena de 80 puntos; etc. */
char *RepiteCad(int longitud, char caracter);
/* pintar un mismo caracter en cualquier fila entre dos columnas dadas */
void PintaFila(int fila, int colini, int colfin, char caracter);
/* pintar un mismo caracter en cualquier columna y entre dos filas dadas */
void PintaCol(int col, int filaini, int filafin, char caracter);
/*Asumir por defecto los caracteres correspondientes a un marco con linea doble. */
void DibujaCuadro(int col_ini, int fila_ini, int col_term, int fila_tenn,
                  const char *bordes = "++++?");
/* borrar los bordes de un recuadro (forma de marco) dibujado en pantalla, indicandoles
las coordenas de las esquinas superior izquierda e inferior derecha. */
void BorraCuadro(int col_ini, int fila_ini, int col_term, int fila_term);
/* borrar el contenido de una area de pantalla indicando/e las coordenadas de las esquinas
superior izquierda e inferior derecha. */
void window(int colini, int filaini, int colfin, int filafin);

void BorraArea(int colini, int filaini, int colfin, int filafin);
/* validar una fecha dada como dia, mes, a�o (dd,mm,aaaa); devolviendo un indicador
l�gico sobre la valid�z � invalid�z de la fecha ingresada. El a�o aceptado debe ser mayor a
1900. */
int ValidaFecha(int dia, int mes, int anio);

/*pantalla y de cualquier longitud devolviendo/o como valor numerico. */
int IngresaEnt(int columna, int fila, int longitud);
/* ingreso de un numero real desde cualquier coordenada de la
pantalla y de cualquier longitud devolviendolo como valor numerico. */
float IngresaReal(int columna, int fila, int longitud);
/* ingreso de una fecha v�lida desde cualquier coordenada de la
pantalla. devuelve por separado el dia, mes y anio. */
void IngresaFecha(int columna, int fila, int &dia, int &mes, int &anio);
/* muestra un mensaje centrado en cualquier fila de la pantalla emitiendo
un sonido de alarma y obligando se presione/a tecla ENTER para continuar.
termina borrando el menesaje en la fila dada. */
void Mensaje(int fila, const char *texto);
/* devolver la respuesta a una pregunta formulada en cualquier fila de pantalla, dando/e en
una cadena el contenido de la pregunta y en otra cadena los caracteres que identifican la
respuesta. */
char Respuesta(int fila, const char *pregunta, const char *respuestas);
/* devolver la respuesta a una pregunta formulada en cualquier fila de pantalla, donde las
alternativas de respuesta solamente sean ENTER o ESC */
char EnterOEsc(int fila, const char *pregunta = "ENTER = continua, ESC = termina");
/* extraer y devolver de una cadena cierta cantidad de caracteres indic�ndole la posici�n a
partir de la cual se desea extraer. */
char *Extraer(const char *cadena, int inicio, int cantidad);
/* insertar una cadena en otra a partir de una posici�n determinada, devolviendo/a. */
char *Insertar(const char *cadena1, const char *cadena2, int posicion);
/* suprimir de una cadena, cierta cantidad de caracteres a partir de una posici�n determinada,
devolviendo/a. */
char *Suprimir(const char *cadena, int posicion, int cantidad);
/* devuelve la posici�n donde se encuentre el contenido de una cadena en otra. */
int PosCad(const char *cadena1, char *cadena2);
/* devuelve en una cadena el formato de cualquier n�mero entero incluyendo comas para
los miles y ap�strofe para los millones. Considera solamente numeros de hasta 9 cifras
enteras. */
char *FormatoNum(float numero, int ndec = 2);
/* dado un mensaje, reemplaza los caracteres que ocupan posiciones impares con digitos
aleatorios comprendidos entre O y 9; devolviendo el nuevo contenido del mensaje. */
unsigned char *MensajeSecreto(const char *mensaje);
/* devuelve la cadena alineada a la derecha completando con espacios en blanco por la
izquierda hasta alcanzar la longitud dada. */
unsigned char *AlineaDer(int longitud, char *cadena);

int MenuPopUp(int col, int fil, char **TextoMenu, int NumOpciones,
              int ConMarco = 1, unsigned char Atributo = 48 + 8 + 7);

int MenuBarra(int col, int fil, const char **TextoMenu, int NumOpciones,
              int espaciado = 3, unsigned char Atributo = 16 + 8 + 7);
/* obtener la fecha del sistema y devolverlo como dia de semana, dia de mes, mes y a�o */
void FechaSistema(int &DiaDeSem, int &Dia, int &Mes, int &Anio);
/* recibe una fecha por separado como dia, mes, a�o y devuelve elf o nnato def echa ddlmml
aaaa como una cadena */
char *FormatoFecha(int d, int m, int a);

// char* IngresaCad(int columna, int fila, int longitud);
char *IngresaCad(int columna, int fila, int longitud, unsigned char atributo = 7);
void gotoxy(int x, int y);

#endif // fin del archivo de cabecera�M�ILIB.h
