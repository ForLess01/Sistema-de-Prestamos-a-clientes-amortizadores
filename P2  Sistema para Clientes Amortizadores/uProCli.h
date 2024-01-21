#if !defined _uProCli_h_
#define _uProCli_h_

#include "_uManInd.h"

typedef char sgStrLibElec[9];

struct sFecha {
    int dia, mes, anio;
};

struct sRegCliente {
    sFecha FechaIng;
    sgStrLibElec LibretaElec;
    char Apellidos[21], Nombres[21];
    char Direccion[41];
    float UltimoSaldo;
    int Prestamos;
    int PrestamoAct;
    int Estado;
};

class cMantIndCli : public cMantArchInd {
private:
    sRegCliente RegCliente;
public:
    cMantIndCli();

    virtual void FormatoPantalla(const char *pvTitulo);
    virtual int IngresaClave();
    virtual void IngresaOtrosCampos();
    virtual void LimpiaEntrada();

    virtual char *Clave();

    virtual void MuestraInformacion();
    virtual void CorrigeInformacion();

    virtual int InformacionActiva();
    virtual int EsAnulable();
    virtual void AnulaInformacion();

    virtual int InformacionMostrable();
    virtual char *Informacion();
    virtual void AsignarEncabezado();

    void mRecibeRegistro(sRegCliente pvRegCliente);
    void mDevuelveRegistro(sRegCliente &prRegCliente);
    char *mApellidosYNombres();
    void mActualizaCliente(sRegCliente pvRegCliente);

    int mObtieneReg(sgStrLibElec pvLibretaElec, sRegCliente &prRegCliente);
};

#endif
