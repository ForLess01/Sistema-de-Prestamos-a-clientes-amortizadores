// protproy.h
#ifndef _PROTPROY_H_
#define _PROTPROY_H_

// constantes globales
#define MaximoRutas 15
#define MaximoTurnos 75
#define MaximoPasajeros 500
#define CapacidadOmnibus 40
#define Ocupado '_'
#define Blanco ' ' // el original es '' en la pag 269
#define Asterisco '*'
#define LineasPorPag 10
#define Falso 0
#define Verdad 1

#define NombreArchRutas "RUTAS.DAT"
#define NombreArchTurnos "TURNOS.DAT"
#define NombreArchPasaj "PASAJERO.DAT"

// defincion de tipos de datos propios

typedef char STR03[4];		   // para el docidog de turno
typedef char STR05[6];		   // para la hora de partida HH:MM
typedef char STR07[8];		   // para la frecuencia de viaje
typedef char STR08[9];		   // para la libreta electoral
typedef char STR15[16];		   // para los apellidos y nombres
typedef char STR30[31];		   // para el nombre de ciudad
typedef char tOmnibus[32][41]; // 40 asientos para 31 dias

// estructura de registro para rutas.....................
struct sRegistroRutas
{
	STR03 CodigoRuta; // autogenerado
	STR30 Ciudad;	  // campo clave de ingreso
	float Tarifa;
	int TotalLibresR, TotalVendidosR;
	float ImporteRuta;
	int Turnos;
	char Status;
};

// estructura de registros para Turnos..............
struct sRegistroTurnos
{
	STR03 CodigoRuta;
	STR03 CodigoTurno; // autogenerado
	STR05 HoraPartida;
	STR07 Frecuencia;
	int TotalLibresT, TotalVendidosT;
	float ImporteTurno;
	tOmnibus Asientos;
	char Status;
};

// estructura de registros para Pasajeros..............
struct sRegistroPasajeros
{
	STR03 CodigoRuta;
	STR03 CodigoTurno;
	int DiaDeViaje, NumeroDeAsiento;
	STR15 ApellidoPaterno, ApellidoMaterno, Nombres;
	int Edad;
	STR08 LibretaElectoral;
};

// estructura de registros para indice de rutas..............
struct sRegIndiceRutas
{
	STR30 Ciudad;
	int Posicion;
};

// estructura de registros para indice de turnos..............
struct sRegIndiceTurnos
{
	STR03 CodigoRuta;
	STR05 HoraPartida;
	int Posicion;
};

// estructura de registros para indice de Pasajeros..............
struct sRegIndicePasajero
{
	STR15 ApellidoPaterno, ApellidoMaterno;
	int Posicion;
};

// prototipo de funciones propias
void Presentacion();
//----------------------------------------------------------
// MODULO DE RUTAS
//----------------------------------------------------------
void EjecutarRutas();
int MenuRutas();

// Ingresos--------------------------------------------------
void IngresoRutas();
void PantallaRutas(char forma);
void IngresaClaveRutas();
int BuscarClavesRutas();
void IngresaOtrosDatosRutas();
void AgregaRegistroRutas();

// Modificacion--------------------------------------------------
void IngresaCodigoRutas();
void RecuperaRegDeRutas(int indice);
int RegRutaesActivo();
void CorrigeCamposdeRuta();
void ActualizarRegEnRutas(int indice);

// Anulacion--------------------------------------------------
void MuestraRegRutas();
char AnuloOActivoRuta();
void AnulaRegRuta();
void ActivaRegRuta();

// Listado-----------------------------------------------------
void Pantalla_ListadoRutas();
void ListaRegRutas(int &fila);
char CambiaPantA(int numero);
void ListaRutas();
//----------------------------------------------------------
//----------------------------------------------------------
// MODULO DE TURNOS
//----------------------------------------------------------
void EjecutaTurnos();
int MenuTurnos();

// Ingresos--------------------------------------------------
void IngresoTurnos();
void PantallaTurnos(char forma);
void IngresaClaveTurnos();
void IngresaVariosTurnos();
void IngresaOtrosDatosTurnos();
char ContinuaIngTurnos();
void AgregaRegTurno();
void ActualizaCamposEnRuta();

// Modificacion----------------------------------------------
void ModificaTurnos();
void CorrigeTurnos();
void IngresaCodigoTurno();
char ContinuaModTurno();
int BuscarRutaTurno();
void RecuperarRegDeTurnos(int indice);
char RegTurnoesActivo();
void CorrigeCamposdeTurno();
void MuestraRegTurno();
void ActualizarRegEnTurnos(int indice);

// Anulacion----------------------------------------------
void AnulaActivaTurnos();
void AnulaActivaRegTurno();
char AnulaOActivaTurnos();
void AnulaRegTurno();
void ActivaRegTurno();

// Listado----------------------------------------------
void ListaTurnos();
void ListadoDeTurnos();
void IngresaClaveListaTurnos();
void ListaTurnosdeRuta();
char RutaenAesRutaenB();
void ListaRegTurno(int &fila);
void PantallaListadoTurnos();
//----------------------------------------------------------
//----------------------------------------------------------
// MODULO DE PASAJES
//----------------------------------------------------------
void EejecutaPasajes();
void PantallaPasajes();
void IngresaTurnoPasajes();

// venta de pasajes----------------------------------------------
void VendePasajes();
void IngresaClavePasajeros();
void MarcaAsientosVendidos();
void IngresaNumeroAsiento();
char ValeNumeroAsiento();
char AsientoDisponible();
void OcuparAsiento();
void IngresarOtrosDatosPasajes();
void AgregarRegPasaj();
void AcumulaTotales(int PasajesVendidos);

// Listado----------------------------------------------
void OrdenaPorApellidos();
void IntercambioPasajeros(sRegIndicePasajero &RegAct, sRegIndicePasajero &RegSig);
//----------------------------------------------------------
// MODULO DE CONSULTAS
//----------------------------------------------------------
void EjecutaConsultas();
int Consultas();

// Consulta de Rutas----------------------------------------------
void ConsultaRutas();
void PantallaConsultaRutas();
void MuestraConsRegRuta(int &fila, int &Libres, int &Vendidos, float &Importe);

// Consulta de Turnos----------------------------------------------
void ConsultaTurnos();
void PantallaConsultaTurnos();
void IngresaClaveConsTurnos();
void MuestraConsTurnosRegRuta();
void ConsultaTurnosDeRuta();
void MuestraConsRegTurno(int &fila);
void MuestraTotalesRegRuta();

// Consultas de Pasajeros
void ConsultaPasajeros();
void PantallaConsultaPasajeros();
void ContinuaConsultaPasajeros();
void IngresaClaveConsPasajeros();
void IngresaTurnoConsPasajeros();
char OtroTurnoConsPasajeros();
void ListaViajeros();
void RecuperaRegdePASAJEROS(int indice);
char RutaTurnoenCesRutaTurnoenB();
void ListaRegPasaj(int &fila);
//----------------------------------------------------------
// MODULO DE INICIALIZACION DE OTRO MES
//----------------------------------------------------------
void InicializaMes();
//----------------------------------------------------------
//----------------------------------------------------------
// MODULO DEl PROYECTO
//----------------------------------------------------------
void Inicializar();
void Ejecutar();
void Finalizar();

void CreaArreglosIndice();

void CreaArregloIndiceDeRutas();
void CreaArregloIndiceDeTurnos();
void CreaArregloIndiceDePasaj();
int IngresarEdad();
#endif // fin dle archivo de cabecera PROTPROY.H
