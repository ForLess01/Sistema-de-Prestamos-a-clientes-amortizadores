#include <string.h>
#include "milib.h"
#include "_uManSec.h"

//----------------------------------------------------------------------

cMantArchSec::cMantArchSec(const char *pvTituloMant,
                            const char *pvNomArchivo,
                            void *prRegistro,
                            int pvTamRegistro,
                            int pvFila1, int pvColumna1,
                            int pvFila2, int pvColumna2,
                            int pvTipoListado):
                    cMantGen( pvTituloMant,
                             pvFila1,pvColumna1,
                             pvFila2,pvColumna2,
                             pvTipoListado)
{
    int voResultado;
    Archivo.Datos(pvNomArchivo, prRegistro, pvTamRegistro);
    voResultado = Archivo.AbrirOCrear();
    if (voResultado == 0)
    {
        ErrorAbrirArchivo(pvNomArchivo, voResultado);
        mRegistraError();
    }
}

//---------------------------------------------------------------------

cMantArchSec::~cMantArchSec()
{
    if(mTodoCorrecto())
    {
        Archivo.Cerrar();
    }
}

//---------------------------------------------------------------------

int cMantArchSec::UbicaClave()
{
    int voPosReg;
    Archivo.IrAlPrimerRegistro();
    for (voPosReg=0; voPosReg < Archivo.mNumRegistros(); voPosReg++)
    {
        Archivo.LeeRegistro();
        if (! ClaveEncontrada())
            Archivo.SgteRegistro();
        else
            return 1;
    }
    return 0;
}

//----------------------------------------------------------------------

void cMantArchSec::ErrorAbrirArchivo(const char *pvNomArchivo,
                                       int pvNumError) //virtual
{
    Mensaje(25,( "No puedo abrir el archivo "+std::string(pvNomArchivo)).c_str());
}
