#if !defined __ULISGEN_H_
#define __ULISGEN_H_

#include <conio.h>
#include "milib.h"
#include "uCadenas.h" // para la clase cCadena
#include "_uTeclado.h" // para la clase cCtrlTeclado
#include "windows.h"
#include "colors.h"

#define ListadoConFiltro 1
#define ListadoSinFiltro 0

// definicion de la clase
class cListGen : public cCtrlTeclado{
private:
    int Fila1, Columna1, Fila2, Columna2,
        ColumnaAct, AnchoPag, ElemPorPag, ElemEnPag,
        LargoInfo, FilasEncabezado;
    long ElemActual,NumElementos,NumProcesados;
    char *ApuntDatos[50];
    char *ApuntEncabezado[2];
    int TipoListado;

public:

    cListGen(int pvFila1 =1, int pvColumna1 =1,
            int pvFila2=24, int pvColumna2=80,
            int pvTipoListado=ListadoSinFiltro);
    void ReiniciaLimites( int pvFila1, int pvColumna1,
                         int pvFila2, int pvColumna2,
                         int pvTipoListado=ListadoSinFiltro);
    virtual void Ejecuta();
    void AsignarMemoriaPagina();
    void DesasignarMemoriaPagina();


    virtual void EvaluaTeclas(uRegTeclado &prTecla);
    virtual void IntentaIrPriPag();
    virtual void IntentaIrUltPag();
    virtual void IntentaIrSgtePag();
    virtual void IntentaIrAntPag();
    virtual void IntentaIrSgteElem();
    virtual void IntentaIrAntElem();
    virtual void IntentaIrDerPag();
    virtual void IntentaIrIzqPag();
    void CargarPrimeraPagina();
    void CargarUltimaPagina();
    void CargarSgtePagina();
    void RealizarLaCarga(long pvElemRetroceder);
    void CargarAntPagina();
    void CargarSgteElem();
    void MoverLineasDesde(int pvDesdeElem);
    void CargarSinFiltro(long pvElemRetroceder);
    void CargaListadoSinFiltro();
    void CargarConFiltro(long pvElemRetroceder);
    void CargaListadoConFiltro();

    void CargarAntElem();
    void CargarHaciaAtras();

private:
    void Avanzar( long pvNumVeces);
    void Retroceder(long pvNumVeces);
    void DeterminarNumElementos();

public:
    virtual void MostrarPagina();
    void MostrarEncabezado();
    void AdicionarEncabezado(const char *pvEncabezado);

private:
    void DesasignarEncabezado();
    void MostrarTeclasPosibles();

public:
    virtual void IrAlInicio() = 0;
    virtual void IrAlFinal() = 0;
    virtual void IrAlSiguiente() = 0;
    virtual void IrAlAnterior() = 0;
    virtual void LeerInformacion() = 0;
    virtual int InformacionMostrable() {return 1;}
    virtual char *Informacion() = 0;
    virtual void AsignarEncabezado() = 0;
    virtual int FinDeListado() { return 1;}
    virtual long NumElementosSinFiltro() = 0;
    virtual void MensajeNoHayInfo();
    virtual void MensajeInicioDeInfo()
        { Mensaje(25, "Inicio de Informacion"); }
    virtual void MensajeFinDeInfo()
        { Mensaje(25, "Fin de Informacion"); }

    // metodos para dar acceso a los campos desde clases descendientes
    long mTotalElementos() { return NumElementos;}
    long mElementoActual() { return ElemActual;}


    void setTextColor(int texto, int background);
};
#endif

