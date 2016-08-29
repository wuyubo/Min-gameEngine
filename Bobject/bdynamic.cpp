#include "bdynamic.h"

namespace Bigo {
    Bdynamic::Bdynamic(QWidget *parent) :
        BdynObj(parent)
    {
        show();
        connect(this, SIGNAL(evt_send_to_thread(BdynObj*)), BglobalObjs::ptEngine(), SLOT(append_new(BdynObj*)));
    }

    Bdynamic::~Bdynamic()
    {

    }

    void Bdynamic::show()
    {
        m_id.exist = true;
        BglobalObjs::dynObjappend(&m_id, this);
    }

    Bbool Bdynamic::doRegion()
    {
        BobjectList_t objList = BglobalObjs::stcObjList();
        foreach (Bobject *bobj, objList) {
            if(!ignoreCrash(bobj)
                    &&bobj->drawArea().site_begin.z == m_area.site_begin.z)
            {
//                if(BglobalObjs::isUpdate()) break;
                if(bobj->m_id.state == BIDDYNAMI && m_id.id == bobj->m_id.dynId->id)
                    continue;
                if(checkIsTouch(bobj))
                {
                    dealCrash(bobj);
                    BglobalObjs::dealfinished();
                    return true;
                }
            }
        }
        BglobalObjs::dealfinished();
        return false;
    }

    Bbool Bdynamic::checkIsTouch(Bobject *bobj)
    {
        return checkStcObj(bobj->drawArea());
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


    void Bdynamic::moveAction()
    {
        switch (m_direction) {
        case UP:
            m_area.site_begin.y -= m_step;
            m_area.site_end.y -= m_step;
            break;
        case DN:
            m_area.site_begin.y += m_step;
            m_area.site_end.y += m_step;
            break;
        case LF:
            m_area.site_begin.x -= m_step;
            m_area.site_end.x -= m_step;
            break;
        case RG:
            m_area.site_begin.x += m_step;
            m_area.site_end.x += m_step;
            break;
        default:
            break;
        }
    }

    void Bdynamic::moveBack()
    {
        switch (m_direction) {
        case UP:
            m_area.site_begin.y += m_beyond;
            m_area.site_end.y += m_beyond;
            break;
        case DN:
            m_area.site_begin.y -= m_beyond;
            m_area.site_end.y -= m_beyond;
            break;
        case LF:
            m_area.site_begin.x += m_beyond;
            m_area.site_end.x += m_beyond;
            break;
        case RG:
            m_area.site_begin.x -= m_beyond;
            m_area.site_end.x -= m_beyond;
            break;
        default:
            break;
        }
        m_beyond = 0;
        updateArea();
    }

    void Bdynamic::kill_myself()
    {
        if(isExist())
        {
            stopMove();
            disconnect(this, SIGNAL(evt_send_to_thread(BdynObj*)), BglobalObjs::ptEngine(), SLOT(append_new(BdynObj*)));
            BglobalObjs::dynObjremove(&m_id);
            m_id.exist = false;
            hook_kill_myself();
        }
    }

    void Bdynamic::hook_kill_myself()
    {

    }

    Bbool Bdynamic::isOutside()
    {
        return false;
    }

    void Bdynamic::dealOutside()
    {

    }

    void Bdynamic::dealCrash(Bobject *bobj)
    {
        bobj = bobj;
    }

    Bbool Bdynamic::ignoreCrash(Bobject *bobj)
    {
        bobj=bobj;
        return false;
    }


}

