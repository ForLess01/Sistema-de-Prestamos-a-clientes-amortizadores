#include <string.h>
#include "_uLisGen.h"


cListGen::cListGen(int pvFila1, int pvColumna1, int pvFila2,
                    int pvColumna2, int pvTipoListado): cCtrlTeclado()
{
    Fila1       = pvFila1;
    Columna1    = pvColumna1;
    Fila2       = pvFila2;
    Columna2    = pvColumna2;
    TipoListado = pvTipoListado;
    AnchoPag	= pvColumna2 - pvColumna1;// + 1;
    ElemPorPag  = pvFila2 - pvFila1; // descontando el aviso de la ult.linea
    FilasEncabezado= 0;
}
//-------------------------------------------------------------------------
void cListGen::ReiniciaLimites( int pvFila1, int pvColumna1,
                                 int pvFila2, int pvColumna2,
                                 int pvTipoListado)
{
    Fila1 = pvFila1;
    Columna1 = pvColumna1;
    Fila2	= pvFila2;
    Columna2 = pvColumna2;
    TipoListado = pvTipoListado;
}
//----------------------------------------------------------------------
void cListGen::AsignarMemoriaPagina()
{
    int voCont;

    // solicitar memoria para los String's que contendran la informacion
    for (voCont = 0; voCont < ElemPorPag; voCont++)
        ApuntDatos[voCont] = new char[LargoInfo+1];
}
//----------------------------------------------------------------------
void cListGen::DesasignarMemoriaPagina()
{
    int voCont;

    for (voCont = 0; voCont < ElemPorPag; voCont++)
        delete (ApuntDatos[voCont]);
}
//----------------------------------------------------------------------
void cListGen::Ejecuta()
{
    if (mTodoCorrecto()) // ?no se ha registrado error ?
    {
        DeterminarNumElementos();
        if (NumElementos == 0)
            MensajeNoHayInfo();
        else
        {
            ColumnaAct = 1;
            LargoInfo = strlen(Informacion());// + 1;
            AsignarEncabezado();
            AsignarMemoriaPagina();
            CargarPrimeraPagina();
            MostrarEncabezado();
            MostrarTeclasPosibles();
            MostrarPagina();
            cCtrlTeclado::Ejecuta();
            DesasignarMemoriaPagina();
            DesasignarEncabezado();
        }
    }
}
//---------------------------------------------------------------------
void cListGen::EvaluaTeclas(uRegTeclado &prTecla)//virtual
{
    if (prTecla.Normal == 0)
        switch (prTecla.Extendida)
        {
            case cgTeclaHome        : IntentaIrPriPag(); break;
            case cgTeclaEnd         : IntentaIrUltPag(); break;
            case cgTeclaPgDn        : IntentaIrSgtePag(); break;
            case cgTeclaPgUp        : IntentaIrAntPag(); break;
            case cgTeclaFlechaAba   : IntentaIrSgteElem(); break;
            case cgTeclaFlechaArr   : IntentaIrAntElem(); break;
            case cgTeclaFlechaDer   : IntentaIrDerPag(); break;
            case cgTeclaFlechaIzq   : IntentaIrIzqPag(); break;
        }
    else
        if(prTecla.Normal == cgTeclaEsc)
        TerminaProcesoTeclas();
}
//------------------------------------------------------------------------
void cListGen::IntentaIrPriPag()//virtual
{
    if (ElemActual <= ElemPorPag+1) // Estamos en la primera pagina?
        MensajeInicioDeInfo();
    else
    {
        CargarPrimeraPagina();
        MostrarPagina();
    }
}
//---------------------------------------------------------------------
void cListGen::IntentaIrUltPag() //virtual
{
    if (ElemActual >= NumElementos) // � estamos en la ultima pagina ?
        MensajeFinDeInfo();
    else
    {
        CargarUltimaPagina();
        MostrarPagina();
    }
}
//---------------------------------------------------------------------
void cListGen::IntentaIrSgtePag()//virtual
{
    if (ElemActual >= NumElementos)// �estamos en la ultima pagina ?
        MensajeFinDeInfo();
    else
    {
        CargarSgtePagina();
        MostrarPagina();
    }
}
//---------------------------------------------------------------------
void cListGen::IntentaIrAntPag()//virtual
{
    if (ElemActual <= ElemPorPag+1) // � estamos en la primera pagina ?
        MensajeInicioDeInfo();
    else
    {
        CargarAntPagina( );
        MostrarPagina();
    }
}
//----------------------------------------------------------------------
void cListGen::IntentaIrSgteElem()//virtual
{
    if (ElemActual >= NumElementos) // � estamos en la Ultima pagina ?
        MensajeFinDeInfo();
    else
    {
        CargarSgteElem();
        MostrarPagina();
    }
}
//---------------------------------------------------------------------

void cListGen::IntentaIrAntElem()//virtual
{
    if (ElemActual <= ElemPorPag+1)// �estamos en la primera pagina ?
        MensajeInicioDeInfo();
    else
    {
        CargarAntElem();
        MostrarPagina();
    }
}
//----------------------------------------------------------------------
void cListGen::IntentaIrDerPag() //virtual
{
    if (ColumnaAct < (LargoInfo - AnchoPag))
    {
        ColumnaAct++;
        MostrarEncabezado();
        MostrarPagina();
    }
}
//------------------------------------------------------------------------
void cListGen::IntentaIrIzqPag()
{
    if (ColumnaAct > 1)
    {
        ColumnaAct--;
        MostrarEncabezado();
        MostrarPagina();
    }
}

//----------------------------------------------------------------------

void cListGen::CargarPrimeraPagina()
{
    ElemActual = 0;
    IrAlInicio();
    CargarSgtePagina();
}

//-----------------------------------------------------------------------

void cListGen::CargarUltimaPagina()
{
    IrAlFinal();
    CargarHaciaAtras();
    /* Avanzar al principio de la siguiente p�gina, dado que se
    ha establecido que siempre se estar� al principio de la
    siguiente p�gina. En este caso nos posicionaremos despues del
    �ltimo elemento */

    IrAlFinal( );
    IrAlSiguiente();
    ElemActual = NumElementos;
}

//---------------------------------------------------------------------

void cListGen::CargarSgtePagina()
{
    if (TipoListado == ListadoSinFiltro)
    {
        ElemEnPag = 0;
        while (ElemActual < NumElementos && ElemEnPag < ElemPorPag)
        {
            LeerInformacion();
            strcpy(ApuntDatos[ElemEnPag] , Informacion());
            ElemActual++;
            ElemEnPag++;
            IrAlSiguiente();
        }
        NumProcesados = ElemEnPag;
    }
    else
    {
        NumProcesados= 0;
        ElemEnPag = 0;
        while (ElemActual < NumElementos && ElemEnPag < ElemPorPag)
        {
            LeerInformacion( );
            if (InformacionMostrable())
            {
                strcpy(ApuntDatos[ElemEnPag] , Informacion());
                ElemActual++;
                ElemEnPag++;
            }
            NumProcesados++;
            IrAlSiguiente();
        }
    }
}

//----------------------------------------------------------------------

void cListGen::RealizarLaCarga(long pvElemRetroceder)
{
    //indicar principio de la siguiente pagina, de la pagina anterior
    ElemActual -= ElemEnPag;

    /* Retroceder los elementos (fisicos) antes procesados, de tal
    manera quenosubiquemos alfinaldela p�gina anterior */
    Retroceder(pvElemRetroceder);

    //cargar la informaci?n
    CargarHaciaAtras();

    /* Avanzar al principio de la siguiente pagina, dado que se ha
    establecido que siempre se estar� al principio dela siguiente p�gina */
    Avanzar(NumProcesados + 1);
}

// ----------------------------------------------------------------------

void cListGen::CargarAntPagina()
{
    if (ElemActual <= (ElemPorPag * 2) + 1) // pag anterior es la primera ?
        CargarPrimeraPagina();
    else
        if (ElemActual <= NumElementos) // ? no estamos en la ?ltima p?gina ?
            RealizarLaCarga(NumProcesados+1);
        else
        {
            IrAlFinal();
            RealizarLaCarga(NumProcesados);
        }
}

//----------------------------------------------------------------------

void cListGen::CargarSgteElem()
{
    int voNumElem;
    if (TipoListado == ListadoSinFiltro)
    {
        // mover la lineas 2 .. ElemPorPag a las lineas 1 .. ElemPorPag-1
        for (voNumElem=0; voNumElem<ElemEnPag-1; voNumElem++)
            strcpy(ApuntDatos[voNumElem], ApuntDatos[voNumElem+1]);

        // cargar la siguiente linea
        LeerInformacion();
        strcpy(ApuntDatos[ElemEnPag], Informacion());

        // Avanzar un elemento
        IrAlSiguiente( );
        ElemActual++;
    }
    else
    {
        // Retroceder al principio de la p�gina
        ElemActual -= ElemEnPag;
        Retroceder(NumProcesados);
        // Avanzar un elemento
        ElemActual++;
        do {
            IrAlSiguiente();
            LeerInformacion( );

        } while(!InformacionMostrable());

        //Realizar la carga
        CargarSgtePagina();
    }
}

//----------------------------------------------------------------------

void cListGen::MoverLineasDesde(int pvDesdeElem)
{
    int voNumElem;

    for (voNumElem=pvDesdeElem; voNumElem > 0; voNumElem--)
        strcpy(ApuntDatos[voNumElem], ApuntDatos[voNumElem-1]);
}

//---------------------------------------------------------------------

void cListGen::CargarSinFiltro(long pvElemRetroceder)
{
    //Cargar la anterior linea
    Retroceder(pvElemRetroceder);
    LeerInformacion( );
    strcpy(ApuntDatos[0], Informacion());

    // Avanzar alprincipio de lasiguiente pagina
    Avanzar(NumProcesados);
}

//---------------------------------------------------------------------
void cListGen::CargaListadoSinFiltro()
{
    // Mover desde la linea 1, en adelante; hacia la linea 2, en adelante
    if (ElemEnPag == ElemPorPag)
        MoverLineasDesde(ElemEnPag);
    else
        MoverLineasDesde(ElemEnPag + 1);
    if (ElemActual <= NumElementos)// no estamos en la �ltima p�gina ?
    {
        CargarSinFiltro(NumProcesados + 1);
        ElemActual--;
    }
    else // Estamos en la �ltima p�gina
    {
        IrAlFinal();
        CargarSinFiltro(NumProcesados);
        if (ElemEnPag == ElemPorPag) // � ultima p?gina completa ?
            ElemActual -- ;
        else
        {
            ElemEnPag++;
            NumProcesados++;
        }
    }
}

//---------------------------------------------------------------------

void cListGen::CargarConFiltro(long pvElemRetroceder)
{
    //Retroceder al principio de la pagina
    Retroceder(pvElemRetroceder);
    do {
        IrAlAnterior();
        LeerInformacion( );
    }while (!InformacionMostrable());

    // Realizar la carga
    CargarSgtePagina();
}

//----------------------------------------------------------------------

void cListGen::CargaListadoConFiltro()
{
    if(ElemActual<=NumElementos)//�no estamos en la ultima pagina?
    {
        ElemActual -= (ElemEnPag+ 1);
        CargarConFiltro(NumProcesados);
    }
    else // Estamos en la ?ltima p?gina
    {
        ElemActual-=(ElemEnPag+1);
        IrAlFinal();
        CargarConFiltro(NumProcesados-1);
    }
}

//-------------------------------------------------------------------------

void cListGen::CargarAntElem()
{
    if (TipoListado == ListadoSinFiltro)
        CargaListadoSinFiltro();
    else
        CargaListadoConFiltro();
}

//--------------------------------------------------------------------------

void cListGen::CargarHaciaAtras()
{
    if(TipoListado==ListadoSinFiltro)
    {
        ElemEnPag = 0;
        while (ElemEnPag < ElemPorPag)
        {
            LeerInformacion();
            strcpy(ApuntDatos [ElemPorPag - ElemEnPag], Informacion());
            ElemEnPag++;
            IrAlAnterior();
        }
        NumProcesados=ElemEnPag;
    }
    else
    {
        NumProcesados= 0;
        ElemEnPag = 0;
        while (ElemEnPag < ElemPorPag)
        {
            LeerInformacion();
            if (InformacionMostrable())
            {
                strcpy(ApuntDatos[ElemPorPag - ElemEnPag] , Informacion());
                ElemEnPag++;
            }
            NumProcesados++;
            IrAlAnterior();
        }
    }
}

//----------------------------------------------------------------------

void cListGen::Avanzar(long pvNumVeces)
{
    while(pvNumVeces>0)
    {
        IrAlSiguiente();
        pvNumVeces--;
    }
}

//------------------------------------------------------------------------

void cListGen::Retroceder(long pvNumVeces)
{
    while(pvNumVeces>0)
    {
        IrAlAnterior();
        pvNumVeces--;
    }
}

//------------------------------------------------------------------

void cListGen::DeterminarNumElementos()
{
    IrAlInicio();
    if (TipoListado == ListadoSinFiltro)
        NumElementos = NumElementosSinFiltro();
    else
    {
        NumElementos = 0;
        while (! FinDeListado())
        {
            LeerInformacion( );
            if (InformacionMostrable())
                NumElementos++;
            IrAlSiguiente();
        }
    }
}

//---------------------------------------------------------------------

void cListGen::MostrarPagina() //virtual
{
    int voFila, voCont;
    cCadena voCadena;
    char cadena[256];

    BorraArea(Columna1, Fila1 + FilasEncabezado, Columna2, Fila2-1);
    voFila = Fila1 + FilasEncabezado;
    for (voCont=0; voCont < ElemEnPag; voCont++)
    {
        if (ColumnaAct > 0)
        {
            strcpy(cadena, Extraer(ApuntDatos[voCont], ColumnaAct-1, AnchoPag));
            EscribeCad(Columna1, voFila, cadena);
        }
        else
            if (strlen(ApuntDatos[voCont]) < AnchoPag)
                EscribeCad(Columna1, voFila, ApuntDatos[voCont]);
            else
                EscribeCad( Columna1, voFila, voCadena.ParteIzq(ApuntDatos[voCont],AnchoPag));
        voFila++;
    }
}

//----------------------------------------------------------------------

void cListGen::MostrarEncabezado()
{
    int voCont;
    cCadena voCadena;
    char cadena[256];

    setTextColor(BLACK, WHITE);

    for (voCont=0; voCont < FilasEncabezado; voCont++)
    {
        strcpy(cadena, Extraer(ApuntEncabezado[voCont], ColumnaAct-1, AnchoPag));
        EscribeCad(Columna1, Fila1 + voCont, voCadena.ConBlancosDer(cadena,AnchoPag));
    }
    if (ColumnaAct == 1)
    {
        if (AnchoPag < LargoInfo)
        {
            EscribeCad(Columna2,Fila1,"");
        }
    }
    else
    {
        EscribeCad(1,Fila1, "");
        if(ColumnaAct + AnchoPag < LargoInfo)
            EscribeCad(Columna2, Fila1, "");
    }

    setTextColor(BLACK, GREEN);
}

//----------------------------------------------------------------------

void cListGen::AdicionarEncabezado(const char*pvEncabezado)
{
    if (FilasEncabezado < 2)
    {
        ApuntEncabezado[FilasEncabezado] = new char[strlen(pvEncabezado)+1];
        strcpy(ApuntEncabezado[FilasEncabezado], (char *)pvEncabezado);
        FilasEncabezado++;
        ElemPorPag-- ;
    }
}

//----------------------------------------------------------------------

void cListGen::DesasignarEncabezado()
{
    while(FilasEncabezado>0)
    {
    FilasEncabezado--;
    delete ApuntEncabezado[FilasEncabezado];
    ElemPorPag++;
    }
    //textattr(7);
}

//----------------------------------------------------------------------

void cListGen::MostrarTeclasPosibles()
{
    const char voSgtePag[17] = "[PgDn] Siguiente";
    const char voAntPag [16] = "[PgUp] Anterior";
    const char voPriPag[14] ="[Home]Inicio";
    const char voUltPag [12] = "[End] Final";
    const char voEscape [12] = "[Esc] Salir";

    const int coAnchoMinCort = 17;
    const int coAnchoTodoCort= 28;
    const int coAnchoMin = 42;
    const int coAnchoTodo = 66;

    char voEspacios[9];
    char *barra = new char[100];
    cCadena voCadena;

    setTextColor(WHITE, BLACK);

    EscribeCad(Columna1, Fila2, RepiteCad(AnchoPag,' '));
    switch (AnchoPag)
    {
        case 70: case 71: case 72: case 73: case 74: case 75:
        case 76: case 77: case 78: case 79: case 80: // entra todo
        {
            strcpy(voEspacios,voCadena.Espacios((AnchoPag-coAnchoTodo)/4));
            strcpy(barra, voSgtePag);
            strcat(barra, voEspacios);
            strcat(barra, voAntPag);
            strcat(barra, voEspacios);
            strcat(barra, voPriPag);
            strcat(barra, voEspacios);
            strcat(barra, voUltPag);
            strcat(barra, voEspacios);
            strcat(barra, voEscape);
            EscribeCad(Columna1, Fila2, barra);
        } break;

        case 44: case 45: case 46: case 47: case 48: case 49: case 50:
        case 51: case 52: case 53: case 54: case 55: case 56: case 57:
        case 58: case 59: case 60: case 61: case 62: case 63: case 64:
        case 65: case 66: case 67: case 68: case 69: // entra lo minimo
        {
            strcpy(voEspacios, voCadena.Espacios((AnchoPag-coAnchoMin)/2));
            strcpy(barra, voSgtePag);
            strcat(barra, voEspacios);
            strcat(barra, voAntPag);
            strcat(barra, voEspacios);
            strcat(barra, voEscape);
            EscribeCad(Columna1, Fila2, voEscape);
        } break;

        case 32: case 33: case 34: case 35: case 36: case 37: case 38:
        case 39: case 40: case 41: case 42: case 43: // entra todo cortado
        {
            strcpy(voEspacios, voCadena.Espacios((AnchoPag-coAnchoTodoCort)/4));
            strcpy(barra, voCadena.ParteIzq( voSgtePag, 6));
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq(voAntPag, 6));
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq( voPriPag, 6));
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq(voUltPag, 5));
            strcat(barra, voEspacios);
            strcat(barra, voUltPag);
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq(voEscape, 5));

            EscribeCad(Columna1, Fila2, barra);
        } break;

        case 19: case 20: case 21: case 22: case 23: case 24: case 25:
        case 26: case 27: case 28: case 29: case 30: case 31:
        // entra minimo cortado
        {
            strcpy(voEspacios,voCadena.Espacios((AnchoPag-coAnchoMinCort)/2));
            strcpy(barra, voCadena.ParteIzq(voSgtePag, 6));
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq(voAntPag, 6));
            strcat(barra, voEspacios);
            strcat(barra, voCadena.ParteIzq(voEscape, 5));

            EscribeCad(Columna1, Fila2, barra);
        } break;

        case 5: case 6: case 7: case 8: case 9: case 10: case 11:
        case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        // entra aviso de escape cortado
            EscribeCad(Columna1, Fila2, voCadena.ParteIzq(voEscape, 5));
    }
    setTextColor(BLACK, GREEN);

    delete barra;
}

//----------------------------------------------------------------------

void cListGen::MensajeNoHayInfo()//virtual
{
    BorraArea(Columna1,Fila1,Columna2, Fila2);
    if (TipoListado == ListadoSinFiltro)
        Mensaje( 12, "No hay informacion registrada");
    else
        Mensaje( 12, "No hay informacion que mostrar");
}

void cListGen::setTextColor(int texto, int background){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Combina los colores de texto y fondo
    int color = (background << 4) | texto;

    SetConsoleTextAttribute(consoleHandle, color);
}
