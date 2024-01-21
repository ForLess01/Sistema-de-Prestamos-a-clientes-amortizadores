#include <string.h>
#include "_uManGen.h"

// ----------------------------------------------------------------------
cMantGen::cMantGen(const char *pvTituloMant,
                     int pvFila1, int pvColumna1,
                     int pvFila2, int pvColumna2,
                     int pvTipoListado):
                cListGen(pvFila1,pvColumna1, pvFila2,pvColumna2, pvTipoListado)
{
    ApuntTitulo = new char[strlen(pvTituloMant)+1];
    strcpy(ApuntTitulo, (char *)pvTituloMant);
}

//----------------------------------------------------------------------

void cMantGen::Ejecuta() //virtual
{
    if (mTodoCorrecto())
    do{
        FormatoPantalla(ApuntTitulo);
        Opcion = Menu();
        RealizaAcciones(Opcion);
    }while (Opcion != 0);
}

//-------------------------------------------------------------------------

cMantGen::~cMantGen()
    { delete ApuntTitulo; }
//----------------------------------------------------------------------

int cMantGen::Menu()
{
    int voOpcion;
    cCadena voCadena;
    const char *opciones[]= { "Ingresa",
                        "Modifica ",
                        "Anula" ,
                        "Consulta" ,
                        "Listado" ,
                        "Fin "};
    EscribeCad( 1,25,voCadena.Espacios(79));
    voOpcion = MenuBarra( 1,25,opciones,6);

    EscribeCad( 1, 25,voCadena.Espacios(79));
    if (voOpcion == 6) voOpcion = 0;
    return voOpcion;
}

// ---------------------------------------------------------------------

void cMantGen::RealizaAcciones(int pvOpcion) //virtual
{
    switch (pvOpcion)
    {
        case 1: Ingresos();           break;
        case 2: Modificacion();       break;
        case 3: Anulacion( );         break;
        case 4: Consulta();           break;
        case 5: Listado();            break;
    }
}

//-----------------------------------------------------------------------

void cMantGen::Ingresos()
{
    int voClaveIngresada;
    do{
        voClaveIngresada = IngresaClave();
        if (voClaveIngresada)
            if (UbicaClave()) // busca la clave y lo encuentra
                Mensaje(25, "Clave ya registrada");
            else // no lo encuentra
            {
            IngresaOtrosCampos();
            AdicionaInformacion();
            }
        LimpiaEntrada();
    } while(voClaveIngresada);
}

//-----------------------------------------------------------------------

void cMantGen::Modificacion()
{
    int voClaveIngresada;
    do {
        voClaveIngresada = IngresaClave();
        if (voClaveIngresada)
            if ( !UbicaClave() ) // busca la clave y NO lo encuentra
                Mensaje(25, "Clave no registrada");
            else // si lo encuentra
            {
                LeerInformacion( );
                if (!InformacionActiva())
                    Mensaje(25, "Informacion anulada");
                else
                {
                    CorrigeInformacion();
                    ActualizaInformacion();
                }
            }
        LimpiaEntrada();
    }while (voClaveIngresada);
}

//--------------------------------------------------------------------------

void cMantGen::Anulacion()
{
    int voClaveIngresada;
    do {
        voClaveIngresada = IngresaClave();
        if (voClaveIngresada)
            if ( !UbicaClave()) // busca la clave y NO lo encuentra
                Mensaje(25, "Clave no registrada");
            else // si lo encuentra
            {
                LeerInformacion( );
                if (EsAnulable())
                {
                    MuestraInformacion( );
                    if (Respuesta(25, "Seguro de Anularlo ? S/N: ","SN") == 'S')
                    {
                        AnulaInformacion( );
                        ActualizaInformacion( );
                    }
                }
            }
        LimpiaEntrada();
    }while(voClaveIngresada);
}

//-------------------------------------------------------------------------

void cMantGen::Consulta()
{
    int voClaveIngresada, voOtraConsulta;
    voOtraConsulta = 1;
    do {
        voClaveIngresada = IngresaClave();
        if (voClaveIngresada)
            if ( !UbicaClave()) // busca la clave y NO lo encuentra
                Mensaje(25, "Clave no registrada");
            else // si lo encuentra
            {
                LeerInformacion();
                if (! InformacionActiva())
                    Mensaje(25, "Informaci?n anulada");
                else
                {
                    MuestraInformacion( );
                    voOtraConsulta = (Respuesta(25, "Desea realizar otra consulta ? S/N: ", "SN") == 'S');
                }
            }
        LimpiaEntrada();
    }while (voClaveIngresada && voOtraConsulta);
}

//------------------------------------------------------------------------

void cMantGen::Listado()//virtual
 { cListGen::Ejecuta();}

// ---------------------------------------------------------------------

int cMantGen::EsAnulable()
{
    // determina si el registro cumple todas las condiciones para su anulacion
    // por defecto, un registro activo es anulable
    if (!InformacionActiva())
        Mensaje(25, "Informacion anulada");
    return InformacionActiva();
}
