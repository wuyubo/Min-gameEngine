#include "bregionthread.h"

namespace Bigo {
    BregionThread::BregionThread(QObject *parent) :
        QThread(parent),
        running(true)
    {

        this->start();
    }
    BregionThread::~BregionThread()
    {

    }

    void BregionThread::run()
    {
        while(running)
        {
            usleep(500);
            checking();
        }
    }
    void BregionThread::checking()
    {
        int i;
        for(i = 0; i<dynObjs.size(); i++)
        {
            checkStcObj(dynObjs[i]);
            checkDynObj(dynObjs[i], i);
        }

    }

    void BregionThread::checkStcObj(BdynObj *dynobj)
    {
        int i;
        bool ret=false;
        for(i = 0; i<stcObjs.size(); i++)
        {
           ret = dynobj->checkIsTouch(stcObjs[i]);
        }
    }

    void BregionThread::checkDynObj(BdynObj *dynobj, int index)
    {
        int i;
        bool ret = false;
        for(i = ++index; i<dynObjs.size(); i++)
        {
            ret = dynobj->checkIsTouch(dynObjs[i]->bobj());

        }
    }

    void BregionThread::stcObjsAppend(Bobject *bobj)
    {
        stcObjs.append(bobj);
    }

    void BregionThread::dynObjsAppend(BdynObj *dobj)
    {
        dynObjs.append(dobj);
    }

    void BregionThread::stop()
    {
        running = false;
        this->exit();
        while(isRunning());
    }
}


