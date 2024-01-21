#if !defined __ULISSEC_H_
#define __ULISSEC_H_

#include "_uArchivo.h"
#include "_uLisGen.h"

// definicion de la clase
class cListArchSec:public cListGen
{
protected:
    cOperaArchivo Archivo;
public:
    cListArchSec( const char *pvNomArchivo,
                void *prRegistro, int pvTamRegistro,
                int pvFila1, int pvColumna1,
                int pvFila2, int pvColumna2,
                int pvTipoListado);
    ~cListArchSec();

    // m�todos necesarios para el listado
    virtual void IrAlInicio() {Archivo.IrAlPrimerRegistro(); }
    virtual void IrAlFinal() {Archivo.IrAlUltimoRegistro(); }
    virtual void IrAlSiguiente() {Archivo.SgteRegistro(); }
    virtual void IrAlAnterior() {Archivo.AntRegistro();}
    virtual void LeerInformacion() {Archivo.LeeRegistro(); }
    virtual int FinDeListado() {return Archivo.FinDeArchivo();}
    virtual long NumElementosSinFiltro(){return Archivo.mNumRegistros(); }

    // metodos adicionales
    virtual void ErrorAbrirArchivo(const char *pvNomArchivo,
                                    int pvNumError);

};

#endif
