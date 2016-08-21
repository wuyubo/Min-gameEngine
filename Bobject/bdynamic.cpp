#include "bdynamic.h"

namespace Bigo {
    Bdynamic::Bdynamic(QWidget *parent) :
        BdynObj(parent)
    {
        m_id.id = BglobalObjs::dynObjsCount();
        BglobalObjs::dynObjsAppend(this);

    }

    Bdynamic::~Bdynamic()
    {
        BglobalObjs::dynObjsremove(m_id.id);
    }

    Bbool Bdynamic::doRegion()
    {
        Bobject *tempObj;
        for(QVector<Bobject*>::Iterator iter = BglobalObjs::gl_allObjs.begin();
            iter != BglobalObjs::gl_allObjs.end(); iter++)
        {
            tempObj = *iter;
            if(!ignoreCrash(tempObj)
                    &&tempObj->drawArea().site_begin.z == m_area.site_begin.z)
            {
                if(tempObj->m_id.state == BIDDYNAMI && m_id.id == tempObj->m_id.dynId->id)
                    continue;
                if(checkIsTouch(tempObj))
                {
                    dealCrash(tempObj);
                    return true;
                }
            }
        }
        return false;
    }

    Bbool Bdynamic::checkIsTouch(Bobject *bobj)
    {
        if(bobj->m_id.state == BIDSTATIC)
        {
            return checkStcObj(bobj->drawArea());
        }
        else if(bobj->m_id.state == BIDDYNAMI) {
            return checkDynObj(BglobalObjs::dynObjReflect(bobj));
        }

        return false;
    }

    Bbool Bdynamic::checkStcObj(Bdarea_t area)
    {
        Bdarea_t tmpA = m_area;
        Bdarea_t tmpB = area;
        switch (m_direction) {
        case UP:
            tmpA.site_end.y += m_step-(m_area.site_end.y-m_area.site_begin.y);
            break;
        case DN:
            tmpA.site_begin.y -= m_step+(m_area.site_end.y-m_area.site_begin.y);
            break;
        case LF:
            tmpA.site_end.x += m_step-(m_area.site_end.x-m_area.site_begin.x);
            break;
        case RG:
            tmpA.site_begin.x -= m_step+(m_area.site_end.x-m_area.site_begin.x);
            break;
        default:
            break;
        }

        if(tmpB.site_end.x <= tmpA.site_begin.x) return false;
        if(tmpB.site_begin.x >= tmpA.site_end.x) return false;

        if(tmpB.site_end.y <= tmpA.site_begin.y) return false;
        if(tmpB.site_begin.y >= tmpA.site_end.y) return false;

        switch (m_direction) {
        case UP:
           m_beyond = tmpB.site_end.y - tmpA.site_begin.y;
            break;
        case DN:
            m_beyond = tmpA.site_end.y - tmpB.site_begin.y;
            break;
        case LF:
            m_beyond = tmpB.site_end.x - tmpA.site_begin.x;
            break;
        case RG:
            m_beyond = tmpA.site_end.x - tmpB.site_begin.x;
            break;
        default:
            break;
        }
        return true;
    }

    Bbool Bdynamic::checkDynObj(BdynObj *dobj)
    {

        return checkStcObj(dobj->m_area);
        switch (m_direction) {
        case UP:
           if(dobj->m_direction != DN ) return checkStcObj(dobj->m_area);
            break;
        case DN:
            if(dobj->m_direction != UP) return checkStcObj(dobj->m_area);
            break;
        case LF:
            if(dobj->m_direction != RG) return checkStcObj(dobj->m_area);
            break;
        case RG:
            if(dobj->m_direction != LF) return checkStcObj(dobj->m_area);
            break;
        default:
            break;
        }
        return true;
    }

    void Bdynamic::dealCrash(Bobject * target)
    {
        target = target;
    }

    Bbool Bdynamic::isTouch()
    {
        if(isOutside())
        {      
            m_isTouch = true;
            moveBack();
            dealOutside();
        }
        else if(doRegion())
        {
            m_isTouch = true;
            moveBack();
        }
        else m_isTouch = false;
        return m_isTouch;
    }

    Bbool Bdynamic::isOutside()
    {
        return false;
    }

    void Bdynamic::dealOutside()
    {

    }

    void Bdynamic::killed()
    {
        this->stopMove();
        m_id.exist = false;
    }

    Bbool Bdynamic::ignoreCrash(Bobject *bobj)
    {
        return false;
    }
}

