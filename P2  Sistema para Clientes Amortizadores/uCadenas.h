#if !defined _UCADENAS_H_
#define _UCADENAS_H_

class cCadena{
public:
    char *Espacios(int pvNumEspacios);
    char *Mayuscula(char *pvCadena);
    char *Minuscula(char *pvCadena);
    char *ParteIzq(const char *pvCadena, int pvNumCars);
    char *ParteDer(const char *pvCadena, int pvNumCars);
    char *SinBlancosIzq(const char *pvCadena);
    char *SinBlancosDer(const char *pvCadena);
    char *SinBlancosIzqDer(const char *pvCadena);
    char *ConBlancosIzq(const char *pvCadena, int pvMaxLongitud);
    char *ConBlancosDer(const char *pvCadena, int pvMaxLongitud);
};


#endif
