#include <string.h>
#include <ctype.h>
#include "milib.h"
#include "uDeftecl.h"
#include "uCadenas.h"

char *cCadena::Espacios(int pvNumEspacios){
    return RepiteCad(pvNumEspacios, cgTeclaEspacio);
}

char *cCadena::Mayuscula(char *pvCadena){
    return strupr(pvCadena);
}

char *cCadena::Minuscula(char *pvCadena){
    return strlwr(pvCadena);
}

char *cCadena::ParteIzq(const char *pvCadena, int pvNumCars){
    return Extraer(pvCadena, 0, pvNumCars);
}

char *cCadena::ParteDer(const char *pvCadena, int pvNumCars){
    return Extraer(pvCadena, strlen(pvCadena) - pvNumCars, pvNumCars);
}

char *cCadena::SinBlancosIzq(const char *pvCadena){
    int voIndice = 0;
    while((voIndice < strlen(pvCadena)) &&
          (pvCadena[voIndice] == cgTeclaEspacio))
        voIndice++;
    return Extraer(pvCadena, voIndice, strlen(pvCadena) - voIndice);
}

char *cCadena::SinBlancosDer(const char *pvCadena){
    int voIndice = strlen(pvCadena);
    while((voIndice >= 0) && (pvCadena[voIndice] == cgTeclaEspacio))
        voIndice--;
    return Extraer(pvCadena, 0, voIndice);
}

char *cCadena::SinBlancosIzqDer(const char *pvCadena){
    return SinBlancosIzq(SinBlancosDer(pvCadena));
}

char *cCadena::ConBlancosIzq(const char *pvCadena, int pvMaxLongitud){
    if(strlen(pvCadena) < pvMaxLongitud)
        return strcat(Espacios(pvMaxLongitud - strlen(pvCadena)), pvCadena);
    else
        if(strlen(pvCadena)>pvMaxLongitud)
            return ParteIzq(pvCadena, pvMaxLongitud);
        else
            return (char *)pvCadena;
}

char *cCadena::ConBlancosDer(const char *pvCadena, int pvMaxLongitud){
    if(strlen(pvCadena) < pvMaxLongitud)
        return Insertar(Espacios(pvMaxLongitud - strlen(pvCadena)),
                        pvCadena, strlen(pvCadena));
    else
        if(strlen(pvCadena)> pvMaxLongitud)
            return ParteIzq(pvCadena, pvMaxLongitud);
        else
            return (char *)pvCadena;
}
