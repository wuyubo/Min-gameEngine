#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "Bobject/btypes.h"

#define WINDOWS_W 1200
#define WINDOWS_H 600
#define BNT_W 100
#define BNT_H 60

enum TANKTYPE{
    ENARMY,
    MEARMY,
    ENTYPE1,
    ENTYPE2,
};

enum DYNIDVALUE{
    IDTANK,
    IDBULL,
    IDSNAK,
};

enum TANKBG{
    TBIGX_BG = 0,
    TBIGY_BG = 0,
    TWIND_BG = (WINDOWS_W-200),
    THEIG_BG = (WINDOWS_H),
};


#endif // GAMEDATA_H
