#if !defined _uProLis4_h_
#define _uProLis4_h_

#include "uProLis2.h"

class cListPrePen : public cListPreOto{
protected:
    virtual int InformacionMostrable();
    virtual void MensajeNoHayInfo();
};

#endif
