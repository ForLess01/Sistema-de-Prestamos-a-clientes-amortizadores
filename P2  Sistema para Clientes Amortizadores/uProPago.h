#if !defined _uProPago_h_
#define _uProPago_h_

#include "_uManSec.h"
#include "uProPres.h"
#include "uProCli.h"

struct sRegPago{
    int NumPago;
    int NumPrestamo;
    sFecha FechaDePago;
    float ImpDePago, ImpDeInt, ImpDeAmort, ImpDeMora;
    char Estado;
};

class cMantSecPag : public cMantArchSec{
private:
    cMantSecPre objPrestamo;
    sRegPrestamo RegPrestamo;
    cMantIndCli objCliente;
    sRegCliente RegCliente;
    sRegPago RegPago;
    int NumeroPago, NumeroPrest;

public:
    cMantSecPag();
    virtual int Menu();
    virtual void RealizaAcciones(int pvOpcion);

    //metodos virtuales para el proceso de Anulacion/Consulta
    virtual void FormatoPantalla(const char *pvTitulo);
    virtual int IngresaClave();
    virtual void IngresaOtrosCampos(){}
    virtual void LimpiaEntrada();
    virtual void AdicionalInformacion();
    int ObtienePrestamo();
    int ObtieneCliente();

    //metodo para el proceso de busqueda
    virtual int ClaveEncontrada();

    virtual void MuestraInformacion();
    virtual void CorrigeInformacion() {}

    virtual int InformacionActiva();
    virtual void AnulaInformacion();

    virtual int InformacionMostrable();
    virtual char *Informacion();
    virtual void AsignarEncabezado();

    void mDevuelveRegistro(sRegPago &prRegPago);
};

#endif
