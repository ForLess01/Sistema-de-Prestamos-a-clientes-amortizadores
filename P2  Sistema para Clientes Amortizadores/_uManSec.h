#if !defined __UMANSEC_H_
#define __UMANSEC_H_

#include "_uArchivo.h"
#include "_uLisGen.h"
#include "_uManGen.h"

// definicion de la clase
class cMantArchSec : public cMantGen
{
private: cOperaArchivo Archivo;
public:
    cMantArchSec(const char *pvTituloMant,
                const char *pvNomArchivo,
                void *prRegistro,
                int pvTamRegistro,
                int pvFila1=1, int pvColumna1=1,
                int pvFila2=24, int pvColumna2=80,
                int pvTipoListado=ListadoSinFiltro);
    ~cMantArchSec();

    // metodos virtuales para el proceso de Ingresos
    virtual int UbicaClave();
    virtual void AdicionaInformacion()
        {Archivo.AdicionaRegistro(); }

    // metodo adicional para el proceso de busqueda
    virtual int ClaveEncontrada()=0;

    // metodos virtuales para el proceso de Modificacion
    virtual void LeerInformacion()
        { Archivo.LeeRegistro(); }

    virtual void ActualizaInformacion()
        { Archivo.ReGrabaRegistro(); }

    // metodos virtuales para el proceso de Listado
    virtual void IrAlInicio()
        { Archivo.IrAlPrimerRegistro(); }

    virtual void IrAlFinal()
        {Archivo.IrAlUltimoRegistro(); }

    virtual void IrAlSiguiente()
        { Archivo.SgteRegistro(); }

    virtual void IrAlAnterior()
        { Archivo.AntRegistro(); }

    virtual int FinDeListado()
        { return Archivo.FinDeArchivo(); }

    virtual long NumElementosSinFiltro()
        { return Archivo.mNumRegistros(); }
    // metodos adicionales
    long NumeroRegistros() { return Archivo.mNumRegistros();}
    virtual void ErrorAbrirArchivo(const char *pvNomArchivo,
                               int pvNumError);
};

#endif
