#if !defined __UMANGEN_H_
#define __UMANGEN_H_

#include "uCadenas.h"
#include "milib.h"
#include "_uLisGen.h"

#define cgOpcIngreso 1
#define cgOpcModificacion 2
#define cgOpcAnulacion 3
#define cgOpcConsulta 4
#define cgOpcListado  5

// definicion de la clase
class cMantGen:public cListGen
{
private:
    char *ApuntTitulo;
    int Opcion;

public:

    cMantGen(const char *pvTituloMant,
            int pvFila1=1, int pyColumna1=1,
            int pvFila2=24, int pvColumna2=80,
            int pvTipoListado=ListadoSinFiltro);
    virtual void Ejecuta();
    ~cMantGen();
    virtual void Ingresos();
    virtual void Modificacion();
    virtual void Anulacion();
    virtual void Consulta();
    virtual void Listado();
    virtual int Menu();
    virtual void RealizaAcciones(int pvOpcion);

    // metodos virtuales para el proceso de Ingresos
    virtual void FormatoPantalla(const char *pvTitulo) = 0;
    virtual int IngresaClave() = 0;
    virtual int UbicaClave() = 0;
    virtual void IngresaOtrosCampos() = 0;
    virtual void LimpiaEntrada() = 0;
    virtual void AdicionaInformacion() = 0;

    // metodos virtuales adicionales para el proceso de Modificacion
    virtual void MuestraInformacion() = 0;
    virtual void CorrigeInformacion() = 0;
    virtual void ActualizaInformacion() = 0;

    // metodos virtuales adicionales para el proceso de Anulacion
    virtual int InformacionActiva() = 0;
    virtual int EsAnulable();
    virtual void AnulaInformacion() = 0;

    // metodos para dar acceso a los campos de clases descendientes
    int mOpcionElegida() {return Opcion;}
};

#endif

