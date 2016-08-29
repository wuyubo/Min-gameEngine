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
        void show();
        virtual Bbool doRegion();
        virtual Bbool checkIsTouch(Bobject *bobj);
        virtual Bbool checkStcObj(Bdarea_t area);
        virtual Bbool checkDynObj(BdynObj *dobj);
        virtual Bbool isTouch();
        virtual void moveAction();
        virtual void moveBack();
        virtual Bbool isOutside();
        virtual void dealOutside();
        virtual void dealCrash(Bobject *bobj);
        virtual Bbool ignoreCrash(Bobject *bobj);
    public:
        virtual void hook_kill_myself();

    public slots:
        virtual void kill_myself();

    };
}


#endif // BDYNAMIC_H
