#include "bglobalobjs.h"
#include <assert.h>

namespace Bigo {

    BThreadEngine *BglobalObjs::gl_ptEngine=NULL;
    QWidget*  BglobalObjs::gl_widget = NULL;
    BobjectMap_t BglobalObjs::gl_map_stcobjs;
    BdynObjMap_t BglobalObjs::gl_map_dynobjs;

    Bu32 BglobalObjs::m_busy = 0;
    BobjectMap_t BglobalObjs::gl_map_stc_cleaner;
    BdynObjMap_t BglobalObjs::gl_map_dyn_cleaner;
    QMap<Bobject *, Bbool> BglobalObjs::gl_map_alive_objs;

    QReadWriteLock BglobalObjs::m_clean_rwlock;
    QMutex BglobalObjs::m_stc_mutex;
    QMutex BglobalObjs::m_dyn_mutex;
    QMutex BglobalObjs::m_busy_mutex;
    QMutex BglobalObjs::m_stc_cleaner_mutex;
    QMutex BglobalObjs::m_dyn_cleaner__mutex;
    QMutex BglobalObjs::m_painting;

    Bbool BglobalObjs::m_update = false;


    BglobalObjs::BglobalObjs(QObject *parent) :
        QObject(parent)
    {
    }


    Bint BglobalObjs::Brand(Bint range)
    {
        int i=qrand();
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000+i);
        return qrand()%range;
    }

    BThreadEngine *BglobalObjs::ptEngine()
    {
         return gl_ptEngine;
    }

    BThreadEngine *BglobalObjs::create_ptEngine(int nThreads, bool bFIFOKeep)
    {
        assert(gl_widget!=NULL);
        if(gl_ptEngine != NULL) realease_ptEngine();
        gl_ptEngine = new BThreadEngine(gl_widget, NULL, nThreads, bFIFOKeep);
        return gl_ptEngine;
    }

    void BglobalObjs::realease_ptEngine()
    {
        delete gl_ptEngine;
        gl_ptEngine = NULL;
    }
    void BglobalObjs::setWidget(QWidget *widget)
    {
        assert(widget!=NULL);
        gl_widget = widget;
    }
    QWidget * BglobalObjs::getWidget()
    {
        return gl_widget;
    }

    bool BglobalObjs::compareObj(const Bobject * a, const Bobject * b)
    {
        assert(a != NULL && b != NULL);
        return a->drawArea().site_begin.z > b->drawArea().site_begin.z;
    }

    BobjectList_t BglobalObjs::stcObjList()
    {
        busy();
        m_clean_rwlock.lockForRead();
        m_stc_mutex.lock();
        BobjectList_t temp = gl_map_stcobjs.values();
        m_stc_mutex.unlock();
        m_clean_rwlock.unlock();
        qSort(temp.begin(), temp.end(), compareObj);
        return temp;
    }

    BdynObjList_t BglobalObjs::dynObjList()
    {
        busy();
        m_clean_rwlock.lockForRead();
        m_dyn_mutex.lock();
        BdynObjList_t temp = gl_map_dynobjs.values();
        m_dyn_mutex.unlock();
        m_clean_rwlock.unlock();
        return temp;
    }

    void BglobalObjs::stcObjappend(BObjId_t *key, Bobject *value)
    {
        assert(key != NULL && value != NULL);
        m_stc_mutex.lock();
        gl_map_stcobjs[key] = value;
        gl_map_alive_objs[value] = true;
        m_stc_mutex.unlock();
    }

    void BglobalObjs::dynObjappend(BdynObjId_t *key, BdynObj *value)
    {
        assert(key != NULL && value != NULL);
        m_dyn_mutex.lock();
        gl_map_dynobjs[key] = value;
        m_dyn_mutex.unlock();
    }

    void BglobalObjs::stcObjremove(BObjId_t *key)
    {
        assert(key != NULL);
        m_painting.lock();
        m_stc_mutex.lock();
        if(gl_map_stcobjs.find(key) != gl_map_stcobjs.end())
        {
            stcRecycle(gl_map_stcobjs[key]);
            gl_map_stcobjs.remove(key);
        }
        m_stc_mutex.unlock();
        m_painting.unlock();
        update();
    }

    void BglobalObjs::dynObjremove(BdynObjId_t *key)
    {
        assert(key != NULL);
        m_painting.lock();
        m_dyn_mutex.lock();
        if(gl_map_dynobjs.find(key) != gl_map_dynobjs.end())
        {
//            dynRecycle(gl_map_dynobjs[key]);
            gl_map_dynobjs.remove(key);
        }
        m_dyn_mutex.unlock();
        m_painting.unlock();
    }

    BdynObj * BglobalObjs::dynObjReflect(BdynObjId_t *key)
    {
        assert(key != NULL);
        m_dyn_mutex.lock();
        BdynObj *temp = gl_map_dynobjs[key];
        m_dyn_mutex.unlock();
        update();
        return temp;
    }
    QList<BObjId_t *> BglobalObjs::stcObjKeys()
    {
        m_stc_mutex.lock();
        QList<BObjId_t *> temp = gl_map_stcobjs.keys();
        m_stc_mutex.unlock();
        return temp;
    }

    Bobject * BglobalObjs::getStcObjbyKey(BObjId_t *key)
    {
        Bobject *temp = NULL;
        m_stc_mutex.lock();
        if(gl_map_stcobjs.find(key) != gl_map_stcobjs.end())
            temp = gl_map_stcobjs[key];
        m_stc_mutex.unlock();
        if(temp != NULL && !temp->m_id.exist)
        {
            delete temp;
            temp = NULL;
        }
        return temp;
    }

    void BglobalObjs::busy()
    {
//        while(isUpdate())
        m_busy_mutex.lock();
        m_busy ++;
        m_busy_mutex.unlock();
    }

    void BglobalObjs::dealfinished()
    {
        m_busy_mutex.lock();
        assert(m_busy>0);
        if(m_busy > 1) m_busy --;
        if(m_busy == 0) m_update = false;
        m_busy_mutex.unlock();
    }

    Bbool BglobalObjs::isBusy()
    {
        Bbool ret = true;
        m_busy_mutex.lock();
        if(m_busy == 0) ret = false;
        m_busy_mutex.unlock();
        return ret;
    }

    void BglobalObjs::stcRecycle(Bobject *bobj)
    {
        assert(bobj != NULL);
//        if(bobj->m_id.state == BIDDYNAMI)
//            dynRecycle(dynObjReflect(bobj->m_id.dynId));

        m_stc_cleaner_mutex.lock();
        if(gl_map_stc_cleaner.find(&(bobj->m_id)) == gl_map_stc_cleaner.end())
            gl_map_stc_cleaner[&(bobj->m_id)]=bobj;
        m_stc_cleaner_mutex.unlock();
    }

    void BglobalObjs::dynRecycle(BdynObj *dobj)
    {
        assert(dobj != NULL);
        m_dyn_cleaner__mutex.lock();
        if(gl_map_dyn_cleaner.find(&(dobj->m_id)) == gl_map_dyn_cleaner.end())
            gl_map_dyn_cleaner[&(dobj->m_id)]=dobj;
        m_dyn_cleaner__mutex.unlock();
    }

    void BglobalObjs::cleanObjs()
    {
//        while(isBusy());

        m_clean_rwlock.lockForWrite();
//        m_dyn_cleaner__mutex.lock();
//        BdynObjList_t dynlist = gl_map_dyn_cleaner.values();
//        if(dynlist.size() > 0)
//            foreach (BdynObj *dobj, dynlist) {
//                if(!dobj->isExist())
//                {
//                    dobj->release();
//                }
//            }
//        gl_map_dyn_cleaner.clear();
//        m_dyn_cleaner__mutex.unlock();
        m_stc_cleaner_mutex.lock();
        BobjectList_t stclist = gl_map_stc_cleaner.values();
        m_painting.lock();
        if(stclist.size()>0)
            foreach (Bobject *bobj, stclist) {
                if(!bobj->isExist())
                {
                    bobj->release();
                }
            }
        m_painting.unlock();
        gl_map_stc_cleaner.clear();
        m_stc_cleaner_mutex.unlock();
        m_clean_rwlock.unlock();
    }

    Bbool BglobalObjs::isUpdate()
    {
        return m_update;
    }

    void BglobalObjs::update()
    {
        m_update = true;
    }

    void BglobalObjs::paint_begin()
    {
        m_painting.lock();
    }

    void BglobalObjs::paint_end()
    {
        m_painting.unlock();
    }
}











