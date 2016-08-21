#ifndef BREGIONTHREAD_H
#define BREGIONTHREAD_H

#include <QThread>
#include <QVector>
#include "Bobject/bobject.h"
#include "Bobject/bdynobj.h"


namespace Bigo {
    class BregionThread : public QThread
    {
        Q_OBJECT
    public:
        explicit BregionThread(QObject *parent = 0);
        ~BregionThread();

    public:
        virtual void run();
        virtual void checking();
        virtual void checkStcObj(BdynObj *dynobj);
        virtual void checkDynObj(BdynObj *dynobj, int index);
        virtual void stcObjsAppend(Bobject *bobj);
        virtual void dynObjsAppend(BdynObj *dobj);
        void stop();
    private:
        QVector<Bobject *> stcObjs;
        QVector<BdynObj *> dynObjs;
        bool running;
//        QVector<BdynObj *> * allObjs;
    };
}


#endif // BREGIONTHREAD_H
