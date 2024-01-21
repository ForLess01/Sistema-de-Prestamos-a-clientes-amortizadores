#if !defined __uIndice_h_
#define __uIndice_h_

#include "_uArchivo.h"
#include <string.h>

struct sRegIndice{
    long Posicion;
    char Clave[21];
};

struct sRegNodo{
    sRegIndice *ApuntIndice;
    sRegNodo *ApuntSgte, *ApuntAnt;
};

class cOperaArchIndice{
protected:
    cOperaArchivo objArchivoInd;
    sRegIndice RegIndice;
    long NumRegistros;
    sRegNodo *ApuntPrimero,
            *ApuntUltimo,
            *ApuntActual;
public:
    void Datos(const char *pvNomArchivo);
    int Crear();
    int Abrir();
    int AbrirOCrear();
    void Cerrar();
    void LeeRegistro();
    void AdicionaRegistro();
    void IrAlPrimerRegistro();
    void IrAlUltimoRegistro();
    void AvanzaRegistros(long pvNumReg);
    void RetrocedeRegistros(long pvNumReg);
    void SgteRegistro();
    void AntRegistro();
    long NumeroRegistros();
    int FinDeArchivo();
private:
    void ArchIndALaLista();
    void ListaAlArchInd();
    void IniciaLista();
    void EliminaLista();
    void CreaNodo();
    void AdicionaRegAlFinal();

public:
    int UbicaClave(const char*pvClave);

    void mPosicionActual(int pvPosicion){RegIndice.Posicion = pvPosicion;}
    void mClaveActual(char *pvClave){strcpy(RegIndice.Clave, pvClave);}
    long mObtienePosicion() {return RegIndice.Posicion;}
    char *mObtieneClaveActual() {return RegIndice.Clave;}

};

#endif
