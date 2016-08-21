#ifndef BDYNAMIC_H
#define BDYNAMIC_H

#include "Bobject/bdynobj.h"
#include "Bobject/bglobalobjs.h"

namespace Bigo {

    class Bdynamic : public BdynObj
    {
        Q_OBJECT
    public:
        explicit Bdynamic(QWidget *parent = 0);
        virtual ~Bdynamic();
        virtual Bbool doRegion();
        virtual Bbool checkIsTouch(Bobject *bobj);
        virtual void dealCrash(Bobject * target);
        virtual Bbool isTouch();
        virtual Bbool isOutside();
        virtual void dealOutside();
        virtual void killed();


    };
}


#endif // BDYNAMIC_H
