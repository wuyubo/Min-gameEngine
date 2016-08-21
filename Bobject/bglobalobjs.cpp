#include "bglobalobjs.h"
#include "Bobject/Bobjects.h"
namespace Bigo {

    QVector<Bobject *> BglobalObjs::gl_stcObjs;
    QVector<BdynObj *> BglobalObjs::gl_dynObjs;
    QVector<Bobject *> BglobalObjs::gl_allObjs;

    BglobalObjs::BglobalObjs(QObject *parent) :
        QObject(parent)
    {
    }

    void BglobalObjs::stcObjsAppend(Bobject *bobj)
    {
        BglobalObjs::gl_stcObjs.append(bobj);
    }

    void BglobalObjs::dynObjsAppend(BdynObj *dobj)
    {
        BglobalObjs::gl_dynObjs.append(dobj);
    }

    void BglobalObjs::allObjsAppend(Bobject *bobj)
    {
        BglobalObjs::gl_allObjs.append(bobj);
    }

    int BglobalObjs::stcObjsCount()
    {
        return gl_stcObjs.size();
    }

    int BglobalObjs::dynObjsCount()
    {
        return gl_dynObjs.size();
    }

    int BglobalObjs::allObjsCount()
    {
        return gl_allObjs.size();
    }

    Bobject *BglobalObjs::stcObjsremove(int index)
    {
        Bobject * temp = gl_stcObjs[index];
        gl_stcObjs.remove(index);
        for(int i=index; i<gl_stcObjs.size(); i++)
        {
            gl_stcObjs[i]->m_id.id--;
        }
        return temp;
    }

    BdynObj *BglobalObjs::dynObjsremove(int index)
    {
        BdynObj * temp = gl_dynObjs[index];
        gl_dynObjs.remove(index);
        for(int i=index; i<gl_dynObjs.size(); i++)
        {
            gl_dynObjs[i]->m_id.id--;
        }
        return temp;
    }

    Bobject *BglobalObjs::allObjsremove(int index)
    {
        Bobject * temp = gl_allObjs[index];
        gl_allObjs.remove(index);
        for(int i=index; i<gl_allObjs.size(); i++)
        {
            gl_allObjs[i]->m_id.id--;
        }
        return temp;
    }

    BdynObj * BglobalObjs::dynObjReflect(Bobject *bobj)
    {
        if(bobj->m_id.state != BIDDYNAMI) return NULL;
        return gl_dynObjs[bobj->m_id.dynId->id];
    }
}
