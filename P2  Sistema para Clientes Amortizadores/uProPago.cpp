#include "uProPago.h"

cMantSecPag::cMantSecPag():
    cMantArchSec("MANTENIMIENTO de PAGOS", "PAGOS.DAT",
                 &RegPago, sizeof(RegPago), 4, 1, 23, 80, ListadoConFiltro)
{
    if(mTodoCorrecto()){
        if(!objPrestamo.mTodoCorrecto()) mRegistraError();
        else
            if(!objCliente.mTodoCorrecto()) mRegistraError();
    }
    else
        mRegistraError();
}


int cMantSecPag::Menu(){
    int voOpcion;
    cCadena voCadena;
    const char *opciones[] = {"Ingreso ",
                        "Anulacion",
                        "Consulta",
                        "Listado",
                        "Fin    "};

    EscribeCad(1, 25, voCadena.Espacios(79));
    voOpcion = MenuBarra(1, 25, opciones, 5);
    EscribeCad(1, 25, voCadena.Espacios(79));
    if(voOpcion == 5)   voOpcion = 0;
    return voOpcion;
}


void cMantSecPag::RealizaAcciones(int pvOpcion){
    switch (pvOpcion){
        case 1: Ingresos(); break;
        case 2: Anulacion(); break;
        case 3: Consulta(); break;
        case 4: Listado(); break;
    }
}


void cMantSecPag::AdicionalInformacion(){
    int voDiaSem, voDia, voMes, voAnio;

    FechaSistema(voDiaSem, voDia, voMes, voAnio);
    RegPago.FechaDePago.dia = voDia;
    RegPago.FechaDePago.mes = voMes;
    RegPago.FechaDePago.anio = voAnio;

    RegPago.NumPago = NumeroPago;
    RegPago.NumPrestamo = NumeroPrest;

    RegPago.ImpDePago = RegPrestamo.Mensualidad;
    RegPago.ImpDeInt = RegPrestamo.MontoDePres * 1.5 / 100;
    RegPago.ImpDeAmort = RegPago.ImpDePago = RegPago.ImpDeInt;
    RegPago.Estado = 1;

    MuestraInformacion();
    if(Respuesta(23, "Esta de acuerdo con los importes?", "SN") == 'S'){
        RegPrestamo.TotalAmort += RegPago.ImpDeAmort;
        RegPrestamo.TotalInt += RegPago.ImpDeInt;
        RegPrestamo.NumPagos++;
        objPrestamo.mRecibeRegistro(RegPrestamo);
        objPrestamo.ActualizaInformacion();

        if(RegPrestamo.NumPagos == RegPrestamo.NumCuotas){
            RegCliente.PrestamoAct = 0;
            objCliente.mActualizaCliente(RegCliente);
        }
        cMantArchSec :: AdicionaInformacion();
    }
}


void cMantSecPag::FormatoPantalla(const char *pvTitulo){
    BorraArea(1, 4, 80, 23);
    CentraCad(1, pvTitulo);

    EscribeCad(20, 6, "Numero de Pago:  ");
    EscribeCad(20, 7, "Numero de Prestamo: ");
    EscribeCad(20, 8, "Cliente: ");
    EscribeCad(20, 10, "Total Deuda: ");
    EscribeCad(20, 11, "Numero de Cuotas: ");
    EscribeCad(20, 12, "Mensualidad: ");
    EscribeCad(20, 13, "Numero de Pagos: ");
    EscribeCad(20, 14, "Total Pagado: ");
    EscribeCad(20, 16, "SALDO de DEUDA: ");

    EscribeCad(20, 18, "Fecha de Pago: ");
    EscribeCad(20, 19, "Importe de Pago: ");
    EscribeCad(20, 20, "Intereses: ");
    EscribeCad(20, 21, "Amortizacion: ");
}


int cMantSecPag::IngresaClave(){
    char voTeclaSalida;
    int voObtieneCliente, voObtienePrestamo;
    cCadena voCadena;

    if(mOpcionElegida()!=cgOpcIngreso){
        CentraCad(23, "PARA TERMINAR, presione solo [ENTER] al ingresar Numero de Pago");
        NumeroPago = IngresaEnt(40, 6, 3);
        EscribeCad(1, 23, voCadena.Espacios(79));
        return (NumeroPago != 0);
    }
    else{
        do{
            CentraCad(23, "PARA TERMINAR, presion solo [ENTER] al ingresar Numero de Prastamo");
            voObtieneCliente = 0;
            voObtienePrestamo = 0;
            NumeroPago = NumeroRegistros() + 1;
            EscribeCad(40, 6, FormatoNum(NumeroPago, 0));
            NumeroPrest = 0;
            EscribeCad(40, 7, voCadena.Espacios(40));
            NumeroPrest = IngresaEnt(40, 7, 3);

            if(NumeroPrest != 0){
                EscribeCad(1, 23, voCadena.Espacios(79));
                voObtienePrestamo = ObtienePrestamo();
                if(voObtienePrestamo){
                    voObtieneCliente = ObtieneCliente();
                    if(voObtieneCliente){
                        char apynomb[80];
                        strcpy(apynomb, Extraer(objCliente.mApellidosYNombres(), 1, 40));
                        EscribeCad(40, 8, apynomb);
                    }
                }
            }
        } while (!(voObtienePrestamo && voObtieneCliente || NumeroPrest == 0));
        return (NumeroPrest!=0);
    }
}


void cMantSecPag::LimpiaEntrada(){
    BorraArea(40, 6, 80, 21);
}

int cMantSecPag::ObtienePrestamo(){
    cCadena voCadena;
    int voObtienePrestamo;

    EscribeCad(1, 23, voCadena.Espacios(79));
    voObtienePrestamo = 0;
    objPrestamo.mRecibeNumeroPrest(NumeroPrest);
    if(!objPrestamo.UbicaClave())
        Mensaje(25, "PRESTAMO NO REGISTRADO");
    else{
        objPrestamo.LeerInformacion();
        objPrestamo.mDevuelveRegistro(RegPrestamo);
        if(!RegPrestamo.Estado)
            Mensaje(25, "PRESTAMO FUE ANULADO");
        else
            if(RegPrestamo.NumCuotas == RegPrestamo.NumPagos)
                Mensaje(25, "PRESTAMO YA ESTA CANCELADO");
            else
                voObtienePrestamo = 1;
    }
    return voObtienePrestamo;
}


int cMantSecPag::ObtieneCliente(){
    int voExisteCliente;
    cCadena voCadena;
    int voObtieneCliente;

    EscribeCad(1, 23, voCadena.Espacios(79));
    voObtieneCliente = 0;
    voExisteCliente = objCliente.mObtieneReg(RegPrestamo.LibretaElec, RegCliente);
    if(!voExisteCliente)
        Mensaje(25, "CLIENTE NO REGISTRADO");
    else
        if(!RegCliente.Estado)
            Mensaje(25, "CLIENTE FUE ANULADO");
        else
            if(!RegCliente.PrestamoAct)
                Mensaje(25, "CLIENTE NO TIENE PRESTAMO PENDIENTE DE PAGO");
            else
                voObtieneCliente = 1;
    return voObtieneCliente;
}


int cMantSecPag::ClaveEncontrada(){
    if(mOpcionElegida() != cgOpcIngreso)
        return (RegPago.NumPago == NumeroPago);
    else
        return 0;
}


void cMantSecPag::MuestraInformacion(){
    cCadena voCadena;

    NumeroPrest = RegPago.NumPrestamo;
    if(mOpcionElegida() != cgOpcIngreso){
        ObtienePrestamo();
        ObtieneCliente();
    }

    EscribeCad(40, 7, voCadena.ConBlancosIzq(FormatoNum(RegPago.NumPrestamo, 0), 3));
    EscribeCad(40, 8, objCliente.mApellidosYNombres());

    EscribeCad(40, 10, voCadena.ConBlancosIzq(
                                        FormatoNum(RegPrestamo.MontoDePres +
                                                   RegPrestamo.MontoDeInt, 2), 10));
    EscribeCad(40, 11, voCadena.ConBlancosIzq(FormatoNum(RegPrestamo.NumCuotas, 0), 10));
    EscribeCad(40, 12, voCadena.ConBlancosIzq(FormatoNum(RegPrestamo.Mensualidad, 2), 10));
    EscribeCad(40, 13, voCadena.ConBlancosIzq(FormatoNum(RegPrestamo.NumPagos, 0), 10));
    EscribeCad(40, 14, voCadena.ConBlancosIzq(
                                        FormatoNum(RegPrestamo.TotalAmort +
                                                   RegPrestamo.TotalInt, 2), 10));
    EscribeCad(40, 16, voCadena.ConBlancosIzq(
                                        FormatoNum(RegPrestamo.MontoDePres +
                                                   RegPrestamo.MontoDeInt -
                                                   RegPrestamo.TotalAmort -
                                                   RegPrestamo.TotalInt, 2), 10));
    EscribeCad(40, 18, FormatoFecha(RegPago.FechaDePago.dia,
                                  RegPago.FechaDePago.mes,
                                  RegPago.FechaDePago.anio));
    EscribeCad(40, 19, voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDePago, 2), 10));
    EscribeCad(40, 20, voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeInt, 2), 10));
    EscribeCad(40, 21, voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeAmort, 2), 10));
}


int cMantSecPag::InformacionActiva(){
    return (RegPago.Estado);
}


void cMantSecPag::AnulaInformacion(){
    RegPago.Estado = 0;
    RegPrestamo.NumPagos--;
    objPrestamo.mRecibeRegistro(RegPrestamo);
    objPrestamo.ActualizaInformacion();
}


int cMantSecPag::InformacionMostrable(){
    return (RegPago.Estado);
}


char *cMantSecPag::Informacion(){
    char cadenas[8][50], cadena[256];
    cCadena voCadena;

    objPrestamo.mRecibeNumeroPrest(RegPago.NumPrestamo);
    if(objPrestamo.UbicaClave()){

        objPrestamo.LeerInformacion();
        objPrestamo.mDevuelveRegistro(RegPrestamo);
        objCliente.mObtieneReg(RegPrestamo.LibretaElec, RegCliente);

        strcpy(cadenas[0], voCadena.ConBlancosIzq(FormatoNum(RegPago.NumPago, 0), 3));
        strcpy(cadenas[1], voCadena.ConBlancosIzq(FormatoNum(RegPago.NumPrestamo, 0), 3));
        strcpy(cadenas[2], voCadena.ConBlancosIzq(FormatoFecha(RegPago.FechaDePago.dia,
                                                           RegPago.FechaDePago.mes,
                                                           RegPago.FechaDePago.anio), 12));
        strcpy(cadenas[3], voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDePago, 2), 10));
        strcpy(cadenas[4], voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeInt, 2), 10));
        strcpy(cadenas[5], voCadena.ConBlancosIzq(FormatoNum(RegPago.ImpDeAmort, 2), 10));
        strcpy(cadenas[6]," ");
        strcpy(cadena, objCliente.mApellidosYNombres());
        strcpy(cadenas[7], voCadena.ConBlancosDer(cadena, 40));

        int longitud, i;
        strcpy(cadena, cadenas[0]);
        longitud = strlen(cadenas[0]);

        for(i=1; i<8; i++){
            strcat(cadena, cadenas[i]);
            longitud += strlen(cadenas[i]);
        }
        cadena[longitud] = '\0';
    }
    else
        cadena[0] = '\0';
    return cadena;
}

void cMantSecPag::AsignarEncabezado(){
    cCadena voCadena;
    char cadenas[8][50], cadena[256];

    strcpy(cadenas[0], voCadena.ConBlancosDer("PAG",       3));
    strcpy(cadenas[1], voCadena.ConBlancosIzq("PRE",       6));
    strcpy(cadenas[2], voCadena.ConBlancosIzq("FECHA",     9));
    strcpy(cadenas[3], voCadena.ConBlancosIzq("IMPORTE",   10));
    strcpy(cadenas[4], voCadena.ConBlancosIzq("INTERES",   10));
    strcpy(cadenas[5], voCadena.ConBlancosIzq("AMORTIZ.",  10));
    strcpy(cadenas[6], " ");
    strcpy(cadenas[7], voCadena.ConBlancosDer("CLIENTE",   20));

    int longitud, i;
    strcpy(cadena, cadenas[0]);
    longitud = strlen(cadenas[0]);

    for(i=1; i<8; i++){
        strcat(cadena, cadenas[i]);
        longitud += strlen(cadenas[i]);
    }
    cadena[longitud] = '\0';
    AdicionarEncabezado(cadena);
}


void cMantSecPag::mDevuelveRegistro(sRegPago &prRegPago){
    prRegPago = RegPago;
}
