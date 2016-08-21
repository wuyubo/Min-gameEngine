#include "tdyncommon.h"

TdynCommon::TdynCommon(QWidget *parent) :
    Bdynamic(parent),
    m_type(ENARMY)
{
}

TdynCommon::~TdynCommon()
{
//    delete m_bomb;
}

Bbool TdynCommon::isOutside()
{
    switch (m_direction) {
    case UP:
        if(m_area.site_begin.y < 0)
        {
            m_beyond = 0-m_area.site_begin.y;
            return true;
        }
        break;
    case DN:
        if(m_area.site_end.y > TBIGY_BG+THEIG_BG)
        {
            m_beyond = m_area.site_end.y - (TBIGY_BG+THEIG_BG);
            return true;
        }
        break;
    case LF:
        if(m_area.site_begin.x < 0)
        {
            m_beyond = 0 - m_area.site_begin.x;
            return true;
        }
        break;
    case RG:
        if(m_area.site_end.x > TBIGX_BG+TWIND_BG)
        {
            m_beyond = m_area.site_end.x - (TBIGX_BG+TWIND_BG);
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void TdynCommon::setType(TANKTYPE type)
{
    m_type = type;
    updateId();
}

void TdynCommon::updateId()
{
    switch (m_type) {
    case MEARMY:
        m_id.fofoe=FRI;
        break;
    case ENARMY:
        m_id.fofoe=FOE;
        break;
    default:
        break;
    }
}

void TdynCommon::bomb()
{
    m_bomb = new Explope(m_widget);
    m_bomb->location(m_area.site_begin.x, m_area.site_begin.y,
                  m_area.site_end.x-m_area.site_begin.x);
}


