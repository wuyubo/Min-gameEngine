#ifndef BTYPES_H
#define BTYPES_H

namespace Bigo {
    typedef int Bint;
    typedef bool Bbool;
    typedef unsigned char Bbyte;
    typedef unsigned short Bu16;
    typedef unsigned int Bu32;
    typedef Bint Bx_t;
    typedef Bx_t By_t;
    typedef Bx_t Bz_t;
    typedef Bx_t Bw_t;
    typedef Bw_t Bh_t;
    typedef struct _site{

        Bx_t x;
        By_t y;
        By_t z;
    }Bsite_t;

    typedef struct _DrawArea{

        Bsite_t site_begin;
        Bsite_t site_end;
    }Bdarea_t;

    enum OBJSTATE{

        EXIST,
        DISAP,
    };

    //identify
    typedef struct _dynobj_id{
        Bbyte id;
        Bbyte fofoe;
        Bbool  exist;
        Bbyte  type;
        Bu32  remain;
    }BdynObjId_t;

    typedef struct _obj_id{
        Bu32 id;
        Bbyte state;
        Bbyte offset;
        Bbool  exist;
        Bbyte  type;
        BdynObjId_t  *dynId;
        Bu32  remain;
    }BObjId_t;

    enum IDVAULE_BSTATE{
        BIDSTATIC,
        BIDDYNAMI,
        BIDBACKGL,
    };

    enum IDVAULE_BTYPE{
        BIDUNKW,
        BIDRECT,
        BIDIMGE,
        BIDELLI,
        BIDLINE,
        BIDPOIN,
        BIDTEXT,
    };
    enum IDVAULE_BFOFOE{
        FRI,
        FOE,
    };

#define DTRUE true
#define DFALSE false

}

#endif // BTYPES_H
