#if !defined _UDEFTECL_H_
#define _UDEFTECL_H_

#define cgTeclaEnter        13
#define cgTeclaEsc          27
#define cgTeclaBackSpace    8
#define cgTeclaFlechaIzq    75
#define cgTeclaFlechaDer    77
#define cgTeclaFlechaArr    72
#define cgTeclaFlechaAba    80
#define cgTeclaHome         71
#define cgTeclaPgDn        81
#define cgTeclaPgUp         73
#define cgTeclaEnd          79
#define cgTeclaTab          9
#define cgTeclaShiftTab     15
#define cgTeclaIns          82
#define cgTeclaDel          83
#define cgTeclaEspacio      32

struct uRegTeclado{
    unsigned int Completo;
    unsigned char Normal, Extendida;
    unsigned char Desde, Hasta;
};

#endif
