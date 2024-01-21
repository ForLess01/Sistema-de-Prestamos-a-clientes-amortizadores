#include <string.h>
#include "milib.h"
#include "_uManInd.h"

//----------------------------------------------------------------------------------------

cMantArchInd::cMantArchInd(const char *pvTituloMant,
                             const char *pvNomArchDat,
                             void *prRegistro,
                             int pvTamRegistro,
                             const char *pvNomArchInd,
                             int pvFila1, int pvColumna1,
                             int pvFila2, int pvColumna2,
                             int pvTipoListado):
                        cMantGen(pvTituloMant,
                            pvFila1,pvColumna1,
                            pvFila2,pvColumna2,
                            pvTipoListado)
{
    int voResultado;
    objArchDato.Datos(pvNomArchDat, prRegistro, pvTamRegistro);
    voResultado = objArchDato.AbrirOCrear();
    if (!voResultado)
    {
        ErrorAbrirArchivo(pvNomArchDat);
        mRegistraError();
    }
    else
    {
        objArchIndice.Datos(pvNomArchInd);
        voResultado = objArchIndice.AbrirOCrear();
        if (voResultado)
        {
            if (objArchDato.mNumRegistros()>
            objArchIndice.NumeroRegistros())
            ReCreaIndice();
        }
        else
        {
            objArchDato.Cerrar();
            ErrorAbrirArchivo(pvNomArchInd);
            mRegistraError();
        }
    }
}

//-------------------------------------------------------------------

cMantArchInd::~cMantArchInd()
{
    if (mTodoCorrecto())
    {
        objArchDato.Cerrar();
        objArchIndice.Cerrar();
  }
}

//--------------------------------------------------------------------

void cMantArchInd::ReCreaIndice()
{
    int voPosReg, voNumReg;
    objArchDato.IrAlPrimerRegistro();
    voNumReg = objArchDato.mNumRegistros();
    for (voPosReg=0; voPosReg < voNumReg; voPosReg++)
    {
        objArchDato.LeeRegistro();
        objArchIndice.mPosicionActual(voPosReg);
        objArchIndice.mClaveActual(Clave());
        objArchIndice.AdicionaRegistro();
        objArchDato.SgteRegistro();
   }
}

//------------------------------------------------------------------------

int cMantArchInd::UbicaClave()//virtual
    { return objArchIndice.UbicaClave(Clave()); }

// -----------------------------------------------------------------------

void cMantArchInd::AdicionaInformacion() //virtual
{
    objArchDato.AdicionaRegistro();
    objArchIndice.mPosicionActual( objArchDato.mNumRegistros()-1 );
    objArchIndice.mClaveActual( Clave());
    objArchIndice.AdicionaRegistro();
}

//----------------------------------------------------------------------------

void cMantArchInd::LeerInformacion() //virtual
{
    objArchIndice.LeeRegistro();
    objArchDato.IrAlRegistro(objArchIndice.mObtienePosicion() + 1);
    objArchDato.LeeRegistro();
}
//-----------------------------------------------------------------------
void cMantArchInd::ActualizaInformacion()  //virtual
{
    objArchIndice.LeeRegistro();
    objArchDato.IrAlRegistro(objArchIndice.mObtienePosicion() + 1);
    objArchDato.ReGrabaRegistro();
}
//-----------------------------------------------------------------------

void cMantArchInd::ErrorAbrirArchivo(const char *pvNomArchivo)
{
    char texto[80];
    strcpy(texto, "No puedo abrir el archivo ");
    strcat(texto, pvNomArchivo);
    Mensaje(25,texto);
}
