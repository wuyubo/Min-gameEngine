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
            if(tempObj->drawArea().site_begin.z == m_area.site_begin.z
                    && m_id.id != tempObj->m_id.dynId->id)
            {
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
        Bdarea_t tmpA = m_area;
        Bdarea_t tmpB = bobj->drawArea();
//        switch (m_direction) {
//        case UP:
//           if(tmpB.site_begin.y > tmpA.site_begin.y
//               && tmpB.site_begin.y > tmpA.site_begin.y + m_speed) return false;
//            break;
//        case DN:
//            if(tmpB.site_begin.y < tmpA.site_begin.y
//                && tmpB.site_begin.y < tmpA.site_begin.y - m_speed) return false;
//            break;
//        case LF:
//            if(tmpB.site_begin.x > tmpA.site_begin.x
//                 && tmpB.site_begin.x > tmpA.site_begin.x+m_speed) return false;
//            break;
//        case RG:
//            if(tmpB.site_begin.x < tmpA.site_begin.x
//                 && tmpB.site_begin.y < tmpA.site_begin.y-m_speed) return false;
//            break;
//        default:
//            break;
//        }
        if(tmpB.site_end.y < tmpA.site_begin.y) return false;
        if(tmpB.site_begin.x > tmpA.site_end.x) return false;
        if(tmpB.site_begin.y > tmpA.site_end.y) return false;
        if(tmpB.site_end.x < tmpA.site_begin.x) return false;
        switch (m_direction) {
        case UP:
            m_beyond = tmpA.site_begin.y - tmpB.site_end.y;
            break;
        case DN:
            m_beyond = tmpA.site_end.y - tmpB.site_begin.y;
            break;
        case LF:
            m_beyond = tmpA.site_begin.x - tmpB.site_end.x;
            break;
        case RG:
            m_beyond = tmpA.site_end.x - tmpB.site_begin.x;
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
}

