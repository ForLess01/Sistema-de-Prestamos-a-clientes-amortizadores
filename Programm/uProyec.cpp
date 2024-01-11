#include "uProyec.h"
#include "milib.h"
#include "ucadenas.h "
#include <conio.h>
// ----------------------------------------------------------------
void cProyecto :: Ejecuta()
{
    int voOpcion;
    do {
        FormatoPantalla( );
        voOpcion = Menu();
        RealizaAcciones(voOpcion);
    } while (voOpcion >= 1 && voOpcion < 5);
}
//----------------------------------------------------------------
int cProyecto:: Menu()
{
    char *opciones[]={
        "CLIENTES  ",
        "PRESTAMOS ",
        "PAGOS     ",
        "CONSULTAS ",
        "FIN",
    };
    int opcion;
    cCadena voCadena;
    
    CentraCad(7,"MENU PRINCIPAL");
    CentraCad(25,"SELECCIONE SU OPCION");
    opcion=MenuPopUp(35,10,opciones,5);
    EscribeCad(1,25,voCadena.Espacios(79));

    return opcion;
}
// ----------------------------------------------------------------
void cProyecto :: FormatoPantalla()
{
    clrscr();
    EscribeCad(1,1,"FINANCIERA AMERICA");
    EscribeCad(1,2,"Av. Trujillo 1170. Telef. 477-3018");
    EscribeCad(1,3,RepiteCad(79,'-'));
    EscribeCad(1,24,RepiteCad(79,'-'));
}
// ----------------------------------------------------------------
void cProyecto :: RealizaAcciones(int pvOpcion)
{
    switch (pvOpcion)
    {
        case 1:
        {
            cMantIndCli objMantIntCli;
            objMantIndCli.Ejecuta();
        }
        break;
        case 2:
        {
            cMantSecPre objMantSecPre;
            objMantSecPre.Ejecuta();
        }
        break;
        case 3:
        {
            cMantSecPag objMantSecPag;
            objMantSecPag.Ejecuta();
        }
        break;
        case 4:
        {
            cProLis objListados;
            objListados.Ejecuta();
        }
        break;
    }
}