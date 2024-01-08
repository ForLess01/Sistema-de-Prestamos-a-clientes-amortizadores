#include "uProPres.h"
#include "milib.h"
#include "ucadenas.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
// ·····················
cMantSecPre::cMantSecPre():cMantArchSec("MANTENIMIENTO de PRESTAMOS", "Prestamo.DAT",&RegPrestamo,sizeof(RegPrestamo),4,1,23,80,ListadoConFiltro)
{
    if(mTodoCorrecto())
    {
        if(!ObjCliente.mTodoCorrecto())
            mRegistraError();
    }
    else
        mRegistraError();
}
//-------------------------------------------------------------------------------------
int cMantSecPre::Menu()
{
    intr voOpcion;
    char *opciones[]={
        "Ingreso ",
        "Consulta ",
        "Listado ",
        "Fin ",
    };
    cCadena voCadena;
    EscribeCad(1,25,voCadena.Espacios(79));
    voOpcion=MenuBarra(1,25,opciones,5);
    EscribeCad(1,25,voCadena.Espacios(79));
    if(voOpcion==5)
        voOpcion=0;
    return voOpcion;
}
//-------------------------------------------------------------------------------------
void cMantSecPre::RealizaAcciones(int pvOpcion)
{
    switch(pvOpcion)
    {
        case l: Ingresos(); break;
        case 2: Anulacion( ); break;
        case 3: Consulta(); break;
        case 4: Listado(); break;
    }
}
//-------------------------------------------------------------------------------------
int cMantSecPre::IngresaClave()
{
    int voClienteHabilitado,voSi;
    cCadena voCadena;

    if(mOpcionElegida()!=cgOpcIngreso)//no se eligio INGRESOS
    {
        CentraCad(22,"PARA TERMINAR, presione solo [ENTER] al ingresar Numero de Prestamo");
        NumeroPrest=IngresaEnt(40,8,3);
        voSi=NumeroPrest !=0;
        EscribeCad(1,22,voCadena.Espacios(79));
    }
    else // SE ELIGIO INGRESOS de PRESTAMOS
    {
        do{
            CentraCad(22,"PARA TERMINAR, presione sólo [ENTER] al ingresar Libreta Electoral");
            voClienteHabilitado=0;
            NumeroPrest=NumeroRegistros()+1;
            EscribeCad(40,8,FormatoNum(NumeroPrest,0));
            EscribeCad(40, 10, voCadena.Espacios(41));
            strcpy(RegCliente.LibretaElec, voCadena.Espacios(8));
            strcpy(RegCliente.LibretaElec,IngresaCad( 40, 9,8));
            if(strlen(RegCliente.LibretaElec)>0)
            {
                EscribeCad( 1, 22, voCadena. Espacios(79) );
                if ( ! ObjCliente.mObtieneReg( RegCliente.LibretaElec,RegCliente))Mensaje(25,"CLIENTE NO REGISTRADO");
                else 
                {
                    char apynomb[81];
                    strcpy(apynomb, voCadena.SinBlancosDer( RegCliente.Apellidos));
                    strcat(apynomb, " ");
                    strcat(apynomb, RegCliente.Nombres);
                    EscribeCad(40,10,apynomb);
                    voClienteHabilitado=ClienteHabilitado();
                }
            }

        }while (!voClienteHabilitado && strlen(RegCliente.LibretraElec)>0);

        voSi=(strlen(RegCliente.LibretaElec)>0);
    }
    return voSi;
}
//-------------------------------------------------------------------------------------
