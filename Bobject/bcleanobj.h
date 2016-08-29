#ifndef BCLEANOBJ_H
#define BCLEANOBJ_H
#include "bdynobj.h"
namespace Bigo {
    class BCleanObj : public BdynObj
    {
        Q_OBJECT
    public:
        explicit BCleanObj(QWidget *parent = 0);
        virtual void run();
        virtual void stopClean();
        virtual void cleaning() = 0;

    private:
        void moveAction();
        void moveBack();
        void updateArea();
        Bbool isTouch();
        Bbool doRegion();

    private slots:
        void kill_myself();

    };
}



#endif // BCLEANOBJ_H
