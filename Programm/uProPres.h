#if !defined _upropres_h_
#define _upropres_h_

#include "uProCli.h"// para la clase cMantlndCli
#include "_umansec.h"// para la clase cMa ntArchSec

//deficion de la estructura de datos de prestamos
struct sRegPrestamo
{
    int NumPrestamo; //campo clave
    sgStrLibElec LibretaElec;
    sFecha FechaDePres;
    float MontoDePressMontoDeInt,TotalAmort,TotalInt,Mensualidad;
    int NumCuotas, NumPagos;
    int Estado; //1:activo, 0:anulado
};

// definicion de la clase
class cMantSecPre : public cMantArchSec
{
    prívate:
    cMantIndCli ObjCliente; // objeto para el acceso al cliente
    sRegCliente RegCliente; // para recibir los datos del cliente
    sRegPrestamo RegPrestamo;
    int NumeroPrest; // para lafuncion ClaveEncontrada de la base
    public:
    cMantSecPre();
    virtual int Menu();
    virtual void RealizaAcciones(int pvOpcion);

    //Metodos virtuales para el proceso de Ingresos.
    virtual void FormatoPantalla(const char *pvTitulo);
    virtual int IngresaClase();
    virtual void IngresaOtrosCampos();
    virtual void LimpiaEntrada();
    int ClienteHabilitado();

    //Metodo para el proceso de busqueda
    virtual int ClaveEncontrada();

    // metodos virtuales para el proceso de Consulta
    virtual void MuestraInformacion();

    // metodos virtuales para el proceso de modificacion
    virtual void CorrigeInformacion(){}

    // metodos virtuales para el proceso de Anulacion
    virtual int InformacionActiva();
    virtual int EsAnulable();
    virtual void AnulaInformacion( );

    // metodos virtuales para el proceso de Listado
    virtual int InformacionMostrable();
    virtual char *Informacion( );
    virtual void AsignarEncabezado( );
    // metodos de comunicacion para el acceso a los datos
    void mRecibeRegistro(sRegPrestamo pvRegPrestamo);
    void mDevuelveRegistro(sRegPrestamo &prRegPrestamo);
    int mObtieneReg(int pvNumeroPrest, sRegPrestamo &prRegPrestamo);

    void mRecibeNumeroPrest(int pvNumeroPrest);
    void mDevuelveCliente( sRegCliente &prRegCliente);
};
#endif // _upropres_h_