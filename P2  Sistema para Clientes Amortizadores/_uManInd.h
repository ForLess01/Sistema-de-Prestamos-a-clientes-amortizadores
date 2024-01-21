#if !defined __UMANIND_H_
#define __UMANIND_H_

#include "_uArchivo.h" // para la clase cOperaArchivo
#include "_uIndice.h" //para la clase cOperaArchIndice
#include "_uLisGen.h"
#include "_uManGen.h"  //para la clase cMantGen

// definicion de la clase
class cMantArchInd : public cMantGen
{
private:
    cOperaArchivo objArchDato;	//objeto para archivo de datos
    cOperaArchIndice objArchIndice; // objeto para archivo indice
public:
    cMantArchInd( const char *pvTituloMant,
                const char *pvNomArchDat,
                void *prRegistro,
                int pvTamRegistro,
                const char *pvNomArchInd,
                int pvFila1 = 1, int pvColumna1=1,
                int pvFila2=24, int pvColumna2=80,
                int pvTipoListado=ListadoConFiltro);

    ~cMantArchInd();
private:
    void ReCreaIndice();
public:
    //metodos virtuales para el proceso de Ingresos
    virtual int UbicaClave();
    virtual void AdicionaInformacion();

    // metodo adicional para el proceso de busqueda
    virtual char *Clave() = 0;

    // metodos virtuales para el proceso de Modificacion
    virtual void LeerInformacion();
    virtual void ActualizaInformacion();

    // metodos virtuales para el proceso de Listado
    virtual void IrAlInicio()
        { objArchIndice.IrAlPrimerRegistro(); }

    virtual void IrAlFinal()
        { objArchIndice.IrAlUltimoRegistro(); }

    virtual void IrAlSiguiente()
        { objArchIndice.SgteRegistro(); }

    virtual void IrAlAnterior()
        { objArchIndice.AntRegistro(); }

    virtual int FinDeListado()
        { return objArchIndice.FinDeArchivo(); }

    virtual long NumElementosSinFiltro()
        { return objArchIndice.NumeroRegistros();}

    // metodos adicionales
    long NumeroRegistros()
        { return objArchIndice.NumeroRegistros(); }

    virtual void ErrorAbrirArchivo(const char *pvNomArchivo);
};
#endif

