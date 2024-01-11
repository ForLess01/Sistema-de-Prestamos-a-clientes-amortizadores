#if!defined _uProLis1_h_
#define _uProLis1_h_
#include "uProPres.h" // para la clase cMantSecPre
#include "uProCli.h"// para fa clase cMantlndCli


// definicion de la clase
class cListPreCli : public cMantSecPre
{
    private:
    cMantIndCli ObjCliente;
    sRegCliente RegCliente;
    sRegPrestamo RegPrestamo;

    public:
    cListPreCli( );
    virtual void Ejecuta();
    virtual int InformacionMostrable( );
    void FormatoListado();
    virtual int IngresaClave();
    void MuestraDatosCliente();
    virtual void AsignarEncabezado( );
    virtual char * Informacion( );
// metodo de comunicacion para el acceso a los datos
void mDevuelveRegCliente( char *pvLibretaElec,
sRegCliente &prRegCliente);

};
#endif 
