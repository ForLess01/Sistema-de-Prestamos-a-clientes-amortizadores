#if !defined _uProCli_h_
#define _uProC[i_h_
#include "_umanind.h"
// definición de un tipo de dato que identifique a la libreta electorial
typedef char sgStrLibElec[9];
// definición de la estrucutra de fecha
struct sFecha
{
    int dia, mes, anio;
};
// definición de la estructura de datos de cliente
struct sRegCliente
{
    sgStrLibElec LibretaElec; // campo clave
    char Apellidos[21], Nombres[21];
    char Direccion[ 4 I];
    sFecha Fechalng;
    float UltimoSaldo;
    int Prestamos;
    int PrestamoAct; // 1 = si tiene, O = no tiene
    int Estado; // I = activo, O = anulado
};
// definicion de la clase
class cMantIndCli : public cMantArchInd
{
private:
    sRegCliente RegCliente;
public:
    // constructor
    cMantIndCli();
    // metodos virtuales para el proceso de Ingresos
    virtual void FormatoPantalla(const char *pvTitulo );
    virtual int IngresaClave();
    virtual void IngresaOtrosCampos();
    virtual void LimpiaEntrada();
    // método para el proceso de busqueda
    virtual char *Clave();
    // metodos virtuales para el proceso de Modifícacion
    virtual void MuestraInformacion();
    virtual void CorrigeInformacion();
    // metodos virtuales para el proceso de Anulacion
    virtual int InformacionActiva();
    virtual int EsAnulable();
    virtual void AnulaInformacion();
    // metodos virtuales para el proceso de Listado
    virtual int InformacionMostrable();
    virtual char *Informacion();
    virtual void AsignarEncabezado();
    // metodo de comunicacion para el acceso a los datos de cliente
    void mRecibeRegistro( sRegCliente pvRegCliente);
    void mDevuelveRegistro(sRegCliente &prRegCliente);
    char *mApellidosYNombres();
    void mActualizaCliente(sRegCliente pvRegCliente);
    int mObtieneReg(sgStrLibElec pvLibretaElec, sRegCliente &prRegCliente);
};
#endif