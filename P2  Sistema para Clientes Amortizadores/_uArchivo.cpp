#include <dos.h>
#include <windows.h>

#include "_uArchivo.h"

void cOperaArchivo::Datos(const char *pvNomArchivo, void *prRegistro,
                          int pvTamRegistro){
    NomArchivo = (char *)pvNomArchivo;
    ApuntRegistro = prRegistro;
    TamRegistro = pvTamRegistro;
    PosPuntero = 0;
}


int cOperaArchivo::Crear(){
    Archivo.open(NomArchivo, std:: ios::out | std::ios::binary);
    NumRegistros = 0;
    return (!Archivo.bad());
}

int cOperaArchivo::Abrir(){
    Archivo.open(NomArchivo, std::ios::in | std::ios::binary);

    Archivo.seekg(0, std::ios::end);
    NumRegistros = Archivo.tellg()/TamRegistro;
    Archivo.seekg(0, std::ios::beg);
    return (!Archivo.bad());
}

int cOperaArchivo::AbrirOCrear(){
    Archivo.open(NomArchivo, std::ios::in | std::ios::out | std::ios::binary);
    Archivo.seekg(0, std::ios::end);
    NumRegistros = Archivo.tellg()/TamRegistro;
    Archivo.seekg(0, std::ios::beg);
    return (!Archivo.bad());
}

void cOperaArchivo::Cerrar(){
    Archivo.flush();
    Archivo.close();
}


void cOperaArchivo::LeeRegistro(){
    Archivo.seekg(PosPuntero *TamRegistro,std::ios::beg);
    Archivo.read((char *)ApuntRegistro, TamRegistro);
}


void cOperaArchivo::ReGrabaRegistro(){
    Archivo.seekg(PosPuntero *TamRegistro, std::ios::beg);
    Archivo.write((char *)ApuntRegistro, TamRegistro);
}

void cOperaArchivo::AdicionaRegistro(){
    Archivo.seekg(0, std::ios::end);
    Archivo.write((char *)ApuntRegistro, TamRegistro);
    NumRegistros++;
    PosPuntero = NumRegistros - 1;
}


void cOperaArchivo::IrAlPrimerRegistro(){
    PosPuntero = 0;
}

void cOperaArchivo::IrAlUltimoRegistro(){
    PosPuntero = NumRegistros - 1;
}

void cOperaArchivo::IrAlRegistro(long pvNumReg){
    PosPuntero = pvNumReg - 1;
}

void cOperaArchivo::AvanzaRegistros(long pvNumReg){
    PosPuntero += pvNumReg;
}

void cOperaArchivo::RetrocedeRegistros(long pvNumReg){
    PosPuntero -= pvNumReg;
}

void cOperaArchivo::SgteRegistro(){
    PosPuntero++;
}

void cOperaArchivo::AntRegistro(){
    PosPuntero--;
}

int cOperaArchivo::AntesDeInicioArch(){
    return (PosPuntero<0);
}

int cOperaArchivo::FinDeArchivo(){
    return (PosPuntero>=NumRegistros);
}

long cOperaArchivo::mNumRegActual(){
    return(PosPuntero + 1);
}

long cOperaArchivo::mNumRegistros(){
    return NumRegistros;
}

void cOperaArchivo::mActualizarReg(void *prRegistro){
    ApuntRegistro = prRegistro;
}

void cOperaArchivo::mObtenerReg(void *prRegistro){
    prRegistro = ApuntRegistro;
}

int cOperaArchivo::mTamRegistro(){
    return (TamRegistro);
}

