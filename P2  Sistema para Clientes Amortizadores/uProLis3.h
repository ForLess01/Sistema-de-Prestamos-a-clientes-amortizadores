#if !defined _uProLis3_h_
#define _uProList3_h_

#include "uProLis2.h"

class cListPreCan : public cListPreOto{
protected:
    virtual int InformacionMostrable();
    virtual void MensajeNoHayInfo();
};

#endif
