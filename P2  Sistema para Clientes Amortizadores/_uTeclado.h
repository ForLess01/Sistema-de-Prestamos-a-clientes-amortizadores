#if !defined __UTECLADO_H_
#define __UTECLADO_H_

#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include "uDeftecl.h"
#include "_uBase.h"

class cCtrlTeclado : public cBase{
public:
    uRegTeclado Tecla;
private:
    int Salir;
public:
    cCtrlTeclado() :cBase(){}
    virtual void Ejecuta();
    virtual void LeerTecla();
    virtual void Leer(uRegTeclado &prTecla);
    virtual void LimpiarTecla();
    virtual void EvaluaTeclas(uRegTeclado &prTecla) = 0;
    virtual void IniciaProcesoTeclas(){Salir = 0;}
    virtual void TerminaProcesoTeclas(){Salir = 1;}

    unsigned char LeerCarNor(const uRegTeclado pvCarsValidos,
                             int pvColumna = 0,
                             int pvFila = 0);
    unsigned char LeerCarExt(const uRegTeclado pvCarsValidos);

    void mObtTecla(uRegTeclado &prTecla) { prTecla = Tecla;}
    unsigned char mUltTeclaNormal() { return Tecla.Normal;}
    unsigned char mUltTeclaExtendida() { return Tecla.Extendida;}
    void gotoxy(int x, int y);
    int wherex();
    int wherey();
};

#endif
