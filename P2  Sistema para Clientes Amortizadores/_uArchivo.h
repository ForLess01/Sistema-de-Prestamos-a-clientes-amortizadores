#if !defined __UARCHIVO_H_
#define __UARCHIVO_H_

#include <iostream>
#include <fstream>

class cOperaArchivo{
private:
    std::fstream Archivo;
    void *ApuntRegistro;
    long PosPuntero, NumRegistros;
    int TamRegistro;
    char *NomArchivo;
public:
    void Datos(const char *pvNomArchivo, void *prRegistro,
               int pvTamRegistro);
    int Crear();
    int Abrir();
    int AbrirOCrear();
    void Cerrar();
    void LeeRegistro();
    void ReGrabaRegistro();
    void AdicionaRegistro();
    void IrAlPrimerRegistro();
    void IrAlUltimoRegistro();
    void IrAlRegistro(long pvNumReg);
    void AvanzaRegistros(long pvNumReg);
    void RetrocedeRegistros(long pvNumReg);
    void SgteRegistro();
    void AntRegistro();
    int AntesDeInicioArch();
    int FinDeArchivo();

    long mNumRegistros();
    long mNumRegActual();
    void mActualizarReg(void *prRegistro);
    void mObtenerReg(void *prRegistro);
    int mTamRegistro();
};

#endif


