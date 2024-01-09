#include "uProLis.h"
#include "uProLis1.h" // para la clase cListPreCli
#include "uProLis2.h" // para la clase cListPreOto
#include "uProLis3.h" // para la clase cListPreCan
#include "uProLis4.h" // para la clase cListPrePen
#include "uProLis5.h" //para la clase cListPagPre
#include "uProLis6.h" // para la clase cListPagos

// --------------------------------------------------------------------------------
void cProLis :: Ejecuta()
{
int voOpcion;

    do {
        voOpcion = Menu();
        RealizaAcciones(voOpcion);
    } while (voOpcion != O);
}
// --------------------------------------------------------------------------------
int cProLis :: Menu()
{

char *opciones[] = { "Prestamos por Cliente ",
                     "Prestamos Otorgados   ",
                     "Prestamos Cancelados  ",
                     "Prestamos Pendientes  ",
                     "Pagos por Prestamo    ",
                     "Pagos Efectuados      ",
                     "Fin                   "
};
int voOpcion;

    BorraArea( 1,4,80,23 ); // borra la zona de trabajo del sistema
    CentraCad(7, "C O N S U L T A S");

    voOpcion = MenuPopU p(30, 10,opciones, 7);
    if (voOpcion == 7)
    voOpcion = O;
    return voOpcion;
}

// --------------------------------------------------------------------------------
void cProLis :: RealizaAcciones(int pvOpcion)
{
    switch ( pvOpcion )
    {
        case 1:
        { cListPreCli objListPreCli;
        objListPreCli.Ejecuta();
        }   break;
        case 2:
        { cListPreOto objListPreOto;
        objListPreOto.Ejecuta();
        } break;
        case 3:
        { cListPreCan objListPreCan;
        objListPreCan.Ejecuta();
        } break;
        case 4:
        { cListPrePen objListPrePen;
        objListPrePen.Ejecuta();
        } break;
        case 5:
        { cListPagPre objListPagPre;
        objListPagPre.Ejecura();
        } break;
        case 6:
        {cListPagos objListPagos;
        objListPagos.Ejecuta();
        } break;
    }
}
// ---------------------------------------------------------------------------------
