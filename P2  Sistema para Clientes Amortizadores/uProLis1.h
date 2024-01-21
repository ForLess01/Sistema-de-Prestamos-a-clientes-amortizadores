#if !defined _uProLis1_h_
#define _uProLis1_h_

#include "uProPres.h" // para la clase cMantSecPre
#include "uProCli.h"	// para la clase cMantIndCli

// definicion de la clase
class cListPreCli : public cMantSecPre {
private:
    cMantIndCli ObjCliente;
    sRegCliente RegCliente;
    sRegPrestamo RegPrestamo;

public:
    cListPreCli();
    virtual void Ejecuta();
    virtual int InformacionMostrable();
    void FormatoListado();
    virtual int IngresaClave();
    void MuestraDatosCliente();
    virtual void AsignarEncabezado();
    virtual char* Informacion();

    // metodo decomunicacion parael acceso al os datos void mDevuelveRegCliente(char *pvLibretaElec, sRegCliente &prRegCliente);
    void mDevuelveRegCliente(char* pvLibretaElec, sRegCliente& prRegCliente);
};

#endif


