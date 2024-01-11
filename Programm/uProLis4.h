#if !defined _uProlis4_h_
#define _uProLis4_h_
#include "uProLis2.h" // para la clase cListPreOto
// definición de la clase
class cListPrePen : public cListPreOto
{
    protected:
        virtual int InformacionMostrable();
        virtual void MensajeNoHayInfo();
};
#endif 