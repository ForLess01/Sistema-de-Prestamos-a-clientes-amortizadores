#include <string.h>
#include "_uIndice.h"

void cOperaArchIndice::Datos(const char *pvNomArchivo){
    NumRegistros = 0;
    objArchivoInd.Datos(pvNomArchivo, &RegIndice, sizeof(RegIndice));
    IniciaLista();
}


int cOperaArchIndice::Crear(){
    return (objArchivoInd.Crear());
}

int cOperaArchIndice::Abrir(){
    int voResultado;
    voResultado = objArchivoInd.Abrir();
    if(objArchivoInd.mNumRegistros() > 0 && voResultado)
        ArchIndALaLista();
    return (voResultado);
}


int cOperaArchIndice::AbrirOCrear(){
    int voResultado;
    voResultado = objArchivoInd.AbrirOCrear();
    if(objArchivoInd.mNumRegistros()>0 && voResultado)
        ArchIndALaLista();
    return voResultado;
}


void cOperaArchIndice::Cerrar(){
    if(NumRegistros > objArchivoInd.mNumRegistros())
        ListaAlArchInd();
    EliminaLista();
    objArchivoInd.Cerrar();
}


void cOperaArchIndice::LeeRegistro(){
    RegIndice = *(ApuntActual->ApuntIndice);
}


void cOperaArchIndice::AdicionaRegistro(){
    sRegNodo *voApuntAux;

    CreaNodo();
    if(ApuntPrimero == NULL){
        ApuntPrimero = ApuntActual;
        ApuntUltimo = ApuntPrimero;
        ApuntPrimero->ApuntAnt = NULL;
        ApuntUltimo->ApuntSgte = NULL;
    }
    else{
        if(strcmp(RegIndice.Clave, ApuntPrimero->ApuntIndice->Clave) < 0){
            ApuntActual->ApuntSgte = ApuntPrimero;
            ApuntPrimero->ApuntAnt = ApuntActual;
            ApuntPrimero = ApuntActual;
            ApuntPrimero->ApuntAnt = NULL;
        }
        else{
            if(strcmp(RegIndice.Clave,
                        ApuntUltimo->ApuntIndice->Clave)>=0){
                ApuntActual->ApuntAnt = ApuntUltimo;
                ApuntUltimo->ApuntSgte = ApuntActual;
                ApuntUltimo = ApuntActual;
                ApuntUltimo->ApuntSgte = NULL;
            }
            else{
                voApuntAux = ApuntPrimero;

                while(strcmp(RegIndice.Clave,
                             voApuntAux->ApuntIndice->Clave) >= 0)
                    voApuntAux = voApuntAux->ApuntSgte;
                ApuntActual->ApuntSgte = voApuntAux;
                ApuntActual->ApuntAnt = voApuntAux->ApuntAnt;
                voApuntAux->ApuntAnt->ApuntSgte = ApuntActual;
                voApuntAux->ApuntAnt = ApuntActual;
            }
        }
    }
    NumRegistros++;
}

void cOperaArchIndice::IrAlPrimerRegistro(){
    ApuntActual = ApuntPrimero;
}

void cOperaArchIndice::IrAlUltimoRegistro(){
    ApuntActual = ApuntUltimo;
}

void cOperaArchIndice::AvanzaRegistros(long pvNumReg){
    while(pvNumReg > 0 && ApuntActual != NULL){
        ApuntActual = ApuntActual->ApuntSgte;
        pvNumReg--;
    }
}

void cOperaArchIndice::RetrocedeRegistros(long pvNumReg){
    while(pvNumReg > 0 && ApuntActual !=NULL){
        ApuntActual = ApuntActual->ApuntAnt;
        pvNumReg--;
    }
}

void cOperaArchIndice::SgteRegistro(){
    if(ApuntActual != NULL)
        ApuntActual = ApuntActual->ApuntSgte;
}

void cOperaArchIndice::AntRegistro(){
    if(ApuntActual !=NULL)
        ApuntActual = ApuntActual->ApuntAnt;
}


long cOperaArchIndice::NumeroRegistros(){ return NumRegistros;}

int cOperaArchIndice::FinDeArchivo(){ return ApuntActual == NULL;}

void cOperaArchIndice::ArchIndALaLista(){
    long voCont;

    NumRegistros = objArchivoInd.mNumRegistros();
    for(voCont = 0; voCont < NumRegistros; voCont++){
        objArchivoInd.LeeRegistro();
        AdicionaRegAlFinal();
        objArchivoInd.SgteRegistro();
    }
    IrAlPrimerRegistro();
}

void cOperaArchIndice::ListaAlArchInd(){
    sRegNodo *voApuntAux;

    objArchivoInd.Cerrar();
    objArchivoInd.Crear();
    objArchivoInd.IrAlPrimerRegistro();
    voApuntAux = ApuntPrimero;
    while(voApuntAux !=NULL){
        RegIndice = *(voApuntAux->ApuntIndice);
        objArchivoInd.AdicionaRegistro();
        voApuntAux = voApuntAux->ApuntSgte;
    }
}

void cOperaArchIndice::IniciaLista(){
    ApuntPrimero = NULL;
    ApuntUltimo = NULL;
}

void cOperaArchIndice::EliminaLista(){
    while(ApuntPrimero != NULL){
        ApuntUltimo = ApuntPrimero->ApuntSgte;
        delete ApuntPrimero;
        ApuntPrimero = ApuntUltimo;
    }
}

void cOperaArchIndice::CreaNodo(){
    ApuntActual = new sRegNodo;

    ApuntActual->ApuntIndice = new sRegIndice;

    *(ApuntActual->ApuntIndice) = RegIndice;
}

void cOperaArchIndice::AdicionaRegAlFinal(){
    CreaNodo();
    ApuntActual->ApuntSgte = NULL;
    ApuntActual->ApuntAnt = ApuntUltimo;
    if(ApuntPrimero == NULL)
        ApuntPrimero = ApuntActual;
    else
        ApuntUltimo->ApuntSgte = ApuntActual;
    ApuntUltimo = ApuntActual;
}

int cOperaArchIndice::UbicaClave(const char *pvClave){
    ApuntActual = ApuntPrimero;
    while(ApuntActual != NULL &&
          strcmp(ApuntActual->ApuntIndice->Clave, pvClave)< 0)
        ApuntActual = ApuntActual->ApuntSgte;
    return(ApuntActual!= NULL &&
           strcmp(ApuntActual->ApuntIndice->Clave, pvClave) == 0);
}

