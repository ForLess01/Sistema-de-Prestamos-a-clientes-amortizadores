/*********************************************************************
Archivo de cabecera : uProLis2.h
*********************************************************************/
#if !deftned _uProlis2_h_
#define _uProLis2_h_
#include "uProPres.h" // para la clase cMantSecPre
// deftnicion de la clase
class cListPreOto : public cMantSecPre
{
    protected:
        sRegPrestamo RegPrestamo;
    public:
        cListPreOto();
        ~cListPreOto( );//alt + 126
        virtual void Ejecuta();
    protected:
            void Totaliza();
        virtual void MensajeNoHayInfo( );
};
#endif 
