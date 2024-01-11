#if !defined _ uProLis3 _h_
#define _uProLis3_h_
#include "uProLis2.h"

// definicion de la clase
// para la clase cListPreOto
class cListPreCan : public cListPreOto
{
    protected:
    virtual int InformacionMostrable( );
    virtual void MensajeNoHayInfo();
};
#endif