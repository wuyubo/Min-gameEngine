#ifndef BGLOBALOBJS_H
#define BGLOBALOBJS_H

#include <QObject>
#include <QVector>
#include <QTime>
#include <QMutex>
#include <QReadWriteLock>
#include "Bobject/bobjects.h"
#include "Bobject/bdynobj.h"
#include "Bthread/bthreadengine.h"

namespace Bigo {

    class BglobalObjs : public QObject
    {
        Q_OBJECT
    public:
        explicit BglobalObjs(QObject *parent = 0);
        static Bint Brand(Bint range);


    public:
        static BThreadEngine *ptEngine();
        static BThreadEngine *create_ptEngine(int nThreads = 2,bool bFIFOKeep = true);
        static void realease_ptEngine();
        static void setWidget(QWidget *widget);
        static QWidget* getWidget();

        static bool compareObj(const Bobject * a, const Bobject * b);
        static BobjectList_t stcObjList();
        static BdynObjList_t dynObjList();    
        static void stcObjappend(BObjId_t *key, Bobject *value);
        static void dynObjappend(BdynObjId_t *key, BdynObj *value);
        static void stcObjremove(BObjId_t *key);
        static void dynObjremove(BdynObjId_t *key);
        static BdynObj * dynObjReflect(BdynObjId_t *key);
        static QList<BObjId_t *> stcObjKeys();
        static Bobject * getStcObjbyKey(BObjId_t *key);

        static void busy();
        static void dealfinished();
        static Bbool isBusy();
        static void stcRecycle(Bobject *bobj);
        static void dynRecycle(BdynObj *dobj);
        static void cleanObjs();

        static Bbool isUpdate();
        static void update();

        static void paint_begin();
        static void paint_end();

    private:
        static BThreadEngine *gl_ptEngine;
        static QWidget* gl_widget;
        static BobjectMap_t gl_map_stcobjs;
        static BdynObjMap_t gl_map_dynobjs;

        static Bu32 m_busy;
        static BobjectMap_t gl_map_stc_cleaner;
        static BdynObjMap_t gl_map_dyn_cleaner;
        static QMap<Bobject *, Bbool> gl_map_alive_objs;

        static QReadWriteLock m_clean_rwlock;
        static QMutex m_stc_mutex;
        static QMutex m_dyn_mutex;
        static QMutex m_busy_mutex;
        static QMutex m_stc_cleaner_mutex;
        static QMutex m_dyn_cleaner__mutex;
        static QMutex m_painting;

        static Bbool m_update;


    };
}

#endif // BGLOBALOBJS_H
