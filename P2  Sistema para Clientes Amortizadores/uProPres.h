#if !defined _upropres_h_
#define _upropres_h_

#include "uProCli.h"
#include "_uManSec.h"

struct sRegPrestamo{
    int NumPrestamo;
    sgStrLibElec LibretaElec;
    sFecha FechaDePres;
    float MontoDePres, MontoDeInt,
            TotalAmort, TotalInt,
            Mensualidad;
    int NumCuotas, NumPagos;
    int Estado; //1=activo, 0=anulado
};

class cMantSecPre : public cMantArchSec{
private:
    cMantIndCli ObjCliente;
    sRegCliente RegCliente;
    sRegPrestamo RegPrestamo;
    int NumeroPrest;

public:
    cMantSecPre();
    virtual int Menu();
    virtual void RealizaAcciones(int pvOpcion);

    virtual void FormatoPantalla(const char *pvTitulo);
    virtual int IngresaClave();
    virtual void IngresaOtrosCampos();
    virtual void LimpiaEntrada();
    int ClienteHabilitado();

    //metodo para el proceso de busqueda
    virtual int ClaveEncontrada();

    //metodos virtuales para el proceso de Consulta
    virtual void MuestraInformacion();

    //metodos virtuales para el proceso de modificaciones
    virtual void CorrigeInformacion();

    //metodos virtuales para el proceso de Anulacion
    virtual int InformacionActiva();
    virtual int EsAnulable();
    virtual void AnulaInformacion();

    //metodos virtuales para el proceso de Listado
    virtual int InformacionMostrable();
    virtual char *Informacion();
    virtual void AsignarEncabezado();

    //metodos de comunicacion para el acceso a los datos
    void mRecibeRegistro(sRegPrestamo pvRegPrestamo);
    void mDevuelveRegistro(sRegPrestamo &prRegPrestamo);
    int mObtieneReg(int pvNumeroPrest, sRegPrestamo &prRegPrestamo);

    void mRecibeNumeroPrest(int pvNumeroPrest);
    void mDevuelveCliente(sRegCliente &prRegCliente);

};

#endif
