#include "bullet.h"

Bullet::Bullet(QWidget *parent) :
    TdynCommon(parent),
    m_r(BR)
{
    m_ellipse = new Bellipse(parent);
    bulletInit();
}

Bullet::Bullet(TANKTYPE type, DIRECTION d, QWidget *parent):
      TdynCommon(parent),
      m_r(BR)
{
      setType(type);
      m_ellipse = new Bellipse(parent);
      m_direction = d;
      bulletInit();

}

Bullet::~Bullet()
{
    m_ellipse->killed();
    delete m_ellipse;
}

void Bullet::bulletInit()
{
    m_id.type = IDBULL;
    m_ellipse->m_id.state = BIDDYNAMI;
    m_ellipse->m_id.dynId = &m_id;
    m_ellipse->setColor(255,255,255);
    m_ellipse->setStyle(ESOLID);
    m_speed = 200;
    m_step = 50;
}


void Bullet::location(int x, int y)
{
    m_area = m_ellipse->createDrawArea(x-m_r, y-m_r, 2*m_r, 2*m_r);
    this->startMove();
}

void Bullet::dealCrash(Bobject *target)
{
    if(target->m_id.state == BIDDYNAMI &&
            target->m_id.dynId->fofoe == m_id.fofoe) return;

    BdynObj *d = BglobalObjs::dynObjReflect(target);
    TdynCommon * tobj= (TdynCommon *)d;
    tobj->bomb();
    tobj->killed();
    this->killed();
}

void Bullet::dealOutside()
{
   bomb();
   this->killed();
}

void Bullet::updateArea()
{
    m_ellipse->setDrawArea(m_area);
}

void Bullet::hook_moveStep()
{
//    if(m_speed < 600)
//        m_speed += 2;
    if(m_step > 20)
        m_step -= 3;
}

