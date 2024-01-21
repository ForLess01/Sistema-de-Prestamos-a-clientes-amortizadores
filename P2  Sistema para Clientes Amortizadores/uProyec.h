#if !defined _uProyec_h_
#define _uProyec_h_

#include "uProCli.h"
#include "uProPres.h"
#include "uProPago.h"
#include "uProLis.h"
#include "_uBase.h"

class cProyecto:public cBase{
public:
    virtual void Ejecuta();
    int Menu();
    void FormatoPantalla();
    void RealizaAcciones(int pvOpcion);
};

#endif
