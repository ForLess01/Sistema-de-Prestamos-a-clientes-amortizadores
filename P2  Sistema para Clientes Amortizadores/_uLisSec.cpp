#include"_uLisSec.h"
#include <string.h>

// ---------------------------------------------------------------------
cListArchSec::cListArchSec( const char *pvNomArchivo,
                             void *prRegistro, int pvTamRegistro,
                             int pvFila1, int pvColumna1,
                             int pvFila2, int pvColumna2,
                             int pvTipoListado):
                    cListGen(pvFila1,pvColumna1,
                            pvFila2,pvColumna2, pvTipoListado)
{
    int voResultado;

    Archivo.Datos(pvNomArchivo, prRegistro, pvTamRegistro);
    voResultado = Archivo.Abrir();
    if (voResultado == 0)
    {
        ErrorAbrirArchivo(pvNomArchivo, voResultado);
        mRegistraError();
    }
}

//---------------------------------------------------------------------

cListArchSec::~cListArchSec()//virtual
{
    if(mTodoCorrecto())
    {
        Archivo.Cerrar();
    }
}

//-----------------------------------------------------------------------

void cListArchSec::ErrorAbrirArchivo(const char *pvNomArchivo,
                                       int pvNumError) //virtual
{
    char texto[80];
    strcpy(texto, "No puedo abrir el archivo ");
    strcat(texto,pvNomArchivo);
    Mensaje(20,texto);
}
