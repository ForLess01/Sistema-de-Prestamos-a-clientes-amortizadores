#if !defined (_uProyec_h_)
#define _uProyec_h_

#include "uProCli.h "// para la clase cMantlndCli
#include "uProPres.h"// para la clase cMantSecPre
#include "uProPago.h"// para la clase cMantSecPag
#include "uProLis.h"// para la clase cProLis
#include "_uBase.h"// para la clase cBase
// dejinicion de la clase
class cProyecto : public cBase
{
public:
    virtual void Ejecuta();
    int Menu();
    void FormatoPantalla();
    void RealizaAcciones(int pvOpcion);
};
#endif