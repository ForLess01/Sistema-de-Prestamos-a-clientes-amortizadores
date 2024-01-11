#include "_umansec.h" // para la clase cMantArchSec
#include "uProPres.h" // para la clase cMantSecPre
#include "uProCli.h"  // para la clase cMantIndCli

#if !defined(_uProPago_h_)
#define _uProPago_h_

// definición de la estructura de datos de pago
struct sRegPago
{
    int NumPago;           // campo clave
    int NumPrestamo;
    sFecha FechaDePago;
    float ImpDePago, ImpDeInt, ImpDeAmort, ImpDeMora;
    char Estado; // true = activo, false = anulado
};

// definicion de la clase
class cMantSecPag : public cMantArchSec
{
private:
    cMantSecPre objPrestamo; // objeto préstamo
    sRegPrestamo RegPrestamo; // para el acceso a los datos del préstamo
    cMantIndCli objCliente; // objeto cliente
    sRegCliente RegCliente; // para el acceso a los datos del cliente
    sRegPago RegPago;
    int NumeroPago, NumeroPrest;

public:
    cMantSecPag();
    virtual int Menu();
    virtual void RealizaAcciones(int pvOpcion);
    // métodos virtuales para el proceso de Anulación/Consulta
    virtual void FormatoPantalla(const char *pvTitulo);
    virtual int IngresaClave();
    virtual void IngresaOtrosCampos(){}
    virtual void LimpiaEntrada();
    virtual void AdicionaInformacion();
    int ObtienePrestamo();
    int ObtieneCliente();
    // método para el proceso de búsqueda
    virtual int ClaveEncontrada();
    // métodos virtuales para el proceso de Consulta
    virtual void MuestraInformacion();
    virtual void CorrigeInformacion() {} // para que no sea abstracta
    // métodos virtuales para el proceso de Anulación
    virtual int InformacionActiva();
    virtual void AnulaInformacion();
    // métodos virtuales para el proceso de Listado
    virtual int InformacionMostrable();
    virtual char *Informacion();
    virtual void AsignarEncabezado();
    // métodos de comunicación para el acceso a los datos
    void DevuelveRegistro(sRegPago &prRegPago);
};

#endif
