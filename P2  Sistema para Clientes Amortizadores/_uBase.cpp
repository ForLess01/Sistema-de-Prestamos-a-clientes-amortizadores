#include "_uBase.h"
#include "milib.h"
#include <Windows.h>

 cBase::cBase(){ TodoCorrecto = 1;}

 void cBase::mRegistraError(){ TodoCorrecto = 0;}

 void cBase::mRegistraExito(){ TodoCorrecto = 1;}

 int cBase::mTodoCorrecto(){ return TodoCorrecto;}

 void cEjecutor::Ahora(cBase *pvObjeto){ pvObjeto->Ejecuta();}


