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

}

void Bullet::bulletInit()
{
    m_id.type = IDBULL;
    m_ellipse->m_id.state = BIDDYNAMI;
    m_ellipse->m_id.dynId = &m_id;
    m_ellipse->setColor(255,255,255);
    m_ellipse->setStyle(ESOLID);
    m_speed = 200;
    m_step = 60;
    connect(this,SIGNAL(evt_bomb(int,int,int)), this, SLOT(bomb(int,int,int)));
}

void Bullet::hook_kill_myself()
{
    disconnect(this,SIGNAL(evt_bomb(int,int,int)), this, SLOT(bomb(int,int,int)));
    m_ellipse->killed();
}

void Bullet::location(int x, int y)
{
    m_area = m_ellipse->createDrawArea(x-m_r, y-m_r, 2*m_r, 2*m_r);
    this->startMove();
}

void Bullet::dealCrash(Bobject *target)
{
    Bdarea_t temp;

    if(target->m_id.state == BIDDYNAMI)
    {
       if(target->m_id.dynId->fofoe == m_id.fofoe) return;
        BdynObj *d = BglobalObjs::dynObjReflect(target->m_id.dynId);
        temp = d->m_area;
    }
    else if(target->m_id.state == BIDSTATIC)
    {
        temp = target->drawArea();
    }

    emit evt_bomb(temp.site_begin.x, temp.site_begin.y,
                  temp.site_end.x-temp.site_begin.x);

    target->killed();
    this->killed();
}

void Bullet::dealOutside()
{
    emit evt_bomb(m_area.site_begin.x-10, m_area.site_begin.y-10,
                     (m_area.site_end.x-m_area.site_begin.x)*2);
    this->killed();

}

void Bullet::updateArea()
{
    m_ellipse->setDrawArea(m_area);
}

void Bullet::hook_moveStep()
{
    if(m_speed < 400)
        m_speed += 2;
    if(m_step > 20)
        m_step -= 3;
}

Bbool Bullet::ignoreCrash(Bobject *bobj)
{
    if(bobj->m_id.state == BIDDYNAMI &&
            bobj->m_id.dynId->fofoe == m_id.fofoe)
        return true;
    return false;
}

void Bullet::bomb(int x, int y, int r)
{
//    Explope::bomb(x, y, r);
}

