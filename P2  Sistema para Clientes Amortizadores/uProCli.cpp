#include "uProCli.h"
#include "milib.h"
#include "uCadenas.h"

cMantIndCli::cMantIndCli() : cMantArchInd("MANTENIMIENTO de CLIENTES",
                                           "Clientes.DAT",
                                           &RegCliente, sizeof(RegCliente),
                                           "Clientes.IND",
                                           4,1,23,80)
{
    if (!mTodoCorrecto())
        mRegistraError();
}

void cMantIndCli::FormatoPantalla(const char *pvTitulo){

    BorraArea(1, 4, 80, 23); // borra la zona de trabajo del sistema
    CentraCad(5, pvTitulo);
    EscribeCad(22, 8, "Libreta Electoral : ");
    EscribeCad(22, 9, "Apellidos");
    EscribeCad(22, 10, "Nombres");
    EscribeCad(22, 11, "Direccion");
    EscribeCad(22, 12, "Fecha de Ingreso : ");
    EscribeCad(22, 13, "Ultimo Saldo : ");
    EscribeCad(22, 14, "Nro. Prestamos :");
    EscribeCad(22, 15, "Prestamo Actual :");
}


int cMantIndCli::IngresaClave() {
    char voTecladoSalida;
    cCadena voCadena;

    CentraCad(22, "PARA TERMINAR, presione solo [ENTER] al ingresa la LIBRETA ELECT.");

    strcpy(RegCliente.LibretaElec, reinterpret_cast<const char*>(IngresaCad(41, 8, 8)));
    EscribeCad(1, 22, voCadena.Espacios(79));

    return (strlen(RegCliente.LibretaElec) > 0);
}


void cMantIndCli::IngresaOtrosCampos() {
    strcpy(RegCliente.Apellidos, reinterpret_cast<const char*>(IngresaCad(41, 9, 20)));
    strcpy(RegCliente.Nombres, reinterpret_cast<const char*>(IngresaCad(41, 10, 20)));
    strcpy(RegCliente.Direccion, reinterpret_cast<const char*>(IngresaCad(41, 11, 40)));
    IngresaFecha(41, 12, RegCliente.FechaIng.dia,
                        RegCliente.FechaIng.mes,
                        RegCliente.FechaIng.anio);

    RegCliente.UltimoSaldo = IngresaReal(41, 13, 8);
    RegCliente.Prestamos = 0;
    RegCliente.PrestamoAct = 0; // no tiene
    RegCliente.Estado = 1;
}


void cMantIndCli::LimpiaEntrada() {
    BorraArea(41, 8, 80, 15);
}


char *cMantIndCli::Clave() {
    return RegCliente.LibretaElec;
}


void cMantIndCli::MuestraInformacion() {
    EscribeCad(41, 8, RegCliente.LibretaElec);
    EscribeCad(41, 9, RegCliente.Apellidos);
    EscribeCad(41, 10, RegCliente.Nombres);
    EscribeCad(41, 11, RegCliente.Direccion);
    EscribeCad(41, 12, FormatoFecha(RegCliente.FechaIng.dia,
                                    RegCliente.FechaIng.mes,
                                    RegCliente.FechaIng.anio));

    EscribeCad(41, 13, FormatoNum(RegCliente.UltimoSaldo, 2));
    EscribeCad(41, 14, FormatoNum(RegCliente.Prestamos, 0));
    if (RegCliente.PrestamoAct)
        EscribeCad(41, 15, "SI TIENE");
    else
        EscribeCad(41, 15, "NO TIENE");
}


void cMantIndCli::CorrigeInformacion() {
    int voCampo;
    const char *opciones[] = {"Apellidos  ",
                        "Nombres    ",
                        "Direccion  ",
                        "Fecha Ingreso  ",
                        "Ultimo Saldo   "};
    MuestraInformacion();
    do {
        voCampo = MenuPopUp(22, 9, opciones, 5, 0);
        switch (voCampo) {
            case 1: strcpy(RegCliente.Apellidos, reinterpret_cast<const char*>(IngresaCad(41, 9, 20))); break;
            case 2: strcpy(RegCliente.Nombres, reinterpret_cast<const char*>(IngresaCad(41, 10, 20))); break;
            case 3: strcpy(RegCliente.Direccion, reinterpret_cast<const char*>(IngresaCad(41, 11, 40))); break;
            case 4: IngresaFecha(41, 12, RegCliente.FechaIng.dia,
                                        RegCliente.FechaIng.mes,
                                        RegCliente.FechaIng.anio); break;
            case 5: if(!RegCliente.PrestamoAct)
                    RegCliente.UltimoSaldo = IngresaReal(41, 13, 8);
                else
                    Mensaje(25, "No puede corregir este campo por tener prestamo");
        }
    } while (voCampo != 0);
}


int cMantIndCli::InformacionActiva() {
    return (RegCliente.Estado);
}


int cMantIndCli::EsAnulable(){
    int voSiEs = 0;

    if(!RegCliente.Estado)
        Mensaje(25, "Cliente ya esta anulado");
    else
        if(RegCliente.PrestamoAct)
            Mensaje(25, "Cliente tiene prestamo");
        else
            voSiEs = 1;
    return voSiEs;
}


void cMantIndCli::AnulaInformacion(){
    RegCliente.Estado = 0;
}


int cMantIndCli::InformacionMostrable(){
    return (RegCliente.Estado);
}


char *cMantIndCli::Informacion(){
    char cadenas[6][50], voInfo[256];
    int longitud;
    cCadena voCadena;

    strcpy(cadenas[0], voCadena.ConBlancosDer(RegCliente.LibretaElec, 10));
    strcpy(cadenas[1], voCadena.ConBlancosDer(RegCliente.Apellidos, 21));
    strcpy(cadenas[2], voCadena.ConBlancosDer(RegCliente.Nombres, 21));
    strcpy(cadenas[3], voCadena.ConBlancosDer(RegCliente.Direccion, 41));
    strcpy(cadenas[4], FormatoFecha(RegCliente.FechaIng.dia,
                                           RegCliente.FechaIng.mes,
                                           RegCliente.FechaIng.anio));
    strcpy(cadenas[5], voCadena.ConBlancosIzq(FormatoNum(RegCliente.UltimoSaldo, 2), 10));

    if(strlen(RegCliente.LibretaElec) > 0){
        strcpy(voInfo, cadenas[0]);
        longitud = strlen(cadenas[0]);

        for(int i=1; i<6; i++){
            strcat(voInfo, cadenas[i]);
            longitud += strlen(cadenas[i]);
        }
        voInfo[longitud] = 0;
    }
    else
        voInfo[0] = 0;
    return voInfo;
}


void cMantIndCli::AsignarEncabezado(){
    char cadenas[6][50], volnfo[256];
    int longitud;
    cCadena voCadena;

    strcpy(cadenas[0], voCadena.ConBlancosDer("ELECTORAL", 10));
    strcpy(cadenas[1], voCadena.ConBlancosDer("APELLIDOS", 21));
    strcpy(cadenas[2], voCadena.ConBlancosDer("NOMBRES", 21));
    strcpy(cadenas[3], voCadena.ConBlancosDer("DIRECCION", 41));
    strcpy(cadenas[4], voCadena.ConBlancosDer("FECHA ING. ", 11));
    strcpy(cadenas[5], voCadena.ConBlancosIzq("ULT. SALDO", 10));

    strcpy(volnfo, cadenas[0]);
    longitud = strlen(cadenas[0]);

    for(int i=1; i<6; i++){
        strcat(volnfo, cadenas[i]);
        longitud += strlen(cadenas[i]);
    }

    volnfo[longitud] = 0;
    AdicionarEncabezado(volnfo);
}


void cMantIndCli::mRecibeRegistro(sRegCliente pvRegCliente){
    RegCliente = pvRegCliente;
}

void cMantIndCli::mDevuelveRegistro(sRegCliente &prRegCliente) {
    prRegCliente = RegCliente;
}

char *cMantIndCli::mApellidosYNombres() {
    char voInfo[80];
    cCadena voCadena;
    strcpy(voInfo, voCadena.SinBlancosDer(RegCliente.Apellidos));
    strcat(voInfo, " ");
    strcat(voInfo, voCadena.SinBlancosDer(RegCliente.Nombres));
    int longitud = strlen(RegCliente.Apellidos) + 1 + strlen(RegCliente.Nombres);

    voInfo[longitud] = '\0';
    return voInfo;
}


void cMantIndCli::mActualizaCliente(sRegCliente pvRegCliente) {
    RegCliente = pvRegCliente;
    ActualizaInformacion();
}


int cMantIndCli::mObtieneReg(sgStrLibElec pvLibretaElec, sRegCliente &prRegCliente) {
    int resultado = 0;
    strcpy(RegCliente.LibretaElec, pvLibretaElec);
    if(UbicaClave()){
        LeerInformacion();
        prRegCliente = RegCliente;
        resultado = 1;
    }
    return resultado;
}
