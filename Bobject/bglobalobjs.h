#ifndef BGLOBALOBJS_H
#define BGLOBALOBJS_H

#include <QObject>
#include <QVector>
#include <QTime>
#include "Bobject/bobjects.h"
#include "Bobject/bdynobj.h"

namespace Bigo {

    class BglobalObjs : public QObject
    {
        Q_OBJECT
    public:
        explicit BglobalObjs(QObject *parent = 0);
        static void stcObjsAppend(Bobject *bobj);
        static void dynObjsAppend(BdynObj *dobj);
        static void allObjsAppend(Bobject *bobj);
        static int stcObjsCount();
        static int dynObjsCount();
        static int allObjsCount();
        static Bobject * stcObjsremove(int index);
        static BdynObj * dynObjsremove(int index);
        static Bobject * allObjsremove(int index);
        static BdynObj * dynObjReflect(Bobject *bobj);
        static Bint Brand(Bint range);
    public:
        static BobjectLists gl_stcObjs;
        static BdynbObjList gl_dynObjs;
        static BobjectLists gl_allObjs;
    };
}

#endif // BGLOBALOBJS_H
