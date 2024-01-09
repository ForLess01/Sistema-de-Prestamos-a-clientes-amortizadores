#if!defined _uProLis1_h_
#define _uProLis1_h_
#include "uProPres.h" // para la clase cMantSecPre
#include "uProCli.h"// para fa clase cMantlndCli


// definicion de la clase
class cListPreCli : public cMantSecPre
{
    private:
    cMantlndCli ObjCliente;
    sRegCliente RegCliente;
    sRegPrestamo RegPrestamo;

    public:
    cListPreCli( );
    virtual void Ejecuta();
    virtual int lnformacionMostrable( );
    void FormatoListado();
    virtual int lngresaClave();
    void MuestraDatosCliente();
    virtual void AsignarEncabezado( );
    virtual char * lnformacion( );
// metodo de comunicacion para el acceso a los datos
void mDevuelveRegCliente( char *pvLibretaElec,
sRegCliente &prRegCliente);

};
#endif 
