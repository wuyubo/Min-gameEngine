#include "tank.h"

Tank::Tank(QWidget *parent):
    TdynCommon(parent)
{
   m_img = new Bimage(parent);
   tankInit();
   qsrand(m_id.id);
}

Tank::Tank(TANKTYPE type, QWidget *parent):
    TdynCommon(parent)
{
    setType(type);
    m_img = new Bimage(parent);
    tankInit();
    setup();
}

Tank::~Tank()
{
    if(running)
        this->stopMove();
    m_img->killed();
    delete m_img;
    delete m_shootTimer;
}

void Tank::tankInit()
{
    m_id.type = IDTANK;
    m_img->m_id.state = BIDDYNAMI;
    m_img->m_id.dynId = &m_id;
    m_shootTimer = new QTimer(m_widget);
    connect(m_shootTimer,SIGNAL(timeout()), this, SLOT(randshoot()));
    src_Init();

}

void Tank::setup()
{
    switch (m_type) {
    case MEARMY:
        creatDrawArea(TBIGX_BG+TWIND_BG/2-TWIDTH/2, TBIGY_BG+THEIG_BG-THEIGHT, TWIDTH, THEIGHT);
        turnDirection(UP);
        break;
    case ENARMY:
        creatDrawArea(TBIGX_BG+(TWIND_BG/3)*((qrand()+m_id.id)%3),
                      TBIGY_BG, TWIDTH, THEIGHT);
        turnDirection(DN);
        this->startMove();
        break;
    default:
        break;
    }
}

void Tank::src_Init()
{
    switch (m_type) {
    case MEARMY:
        m_img_src[UP] = "img/tank/tankmup_me.png";
        m_img_src[DN] = "img/tank/tankmdn_me.png";
        m_img_src[LF] = "img/tank/tankmlf_me.png";
        m_img_src[RG] = "img/tank/tankmrg_me.png";
        m_img_src[EN] = "img/tank/bomb.png";
        break;
    case ENARMY:
        m_img_src[UP] = "img/tank/tankmup.png";
        m_img_src[DN] = "img/tank/tankmdn.png";
        m_img_src[LF] = "img/tank/tankmlf.png";
        m_img_src[RG] = "img/tank/tankmrg.png";
        m_img_src[EN] = "img/tank/bomb.png";
        break;
    default:
        break;
    }
}



void Tank::turnDirection(DIRECTION d)
{
    m_direction = d;
    m_img->setPath(m_img_src[m_direction]);
    m_widget->update();
}


void Tank::creatDrawArea(int x, int y, int w, int h)
{
    m_area = m_img->createDrawArea(x, y, w, h);
}

void Tank::setType(TANKTYPE type)
{
    m_type = type;
    updateId();
    src_Init();
}


void Tank::reloadBullet()
{
    Bullet *newBullet = new Bullet(m_type, m_direction, m_widget);
    Bdarea_t tmp_area = m_img->drawArea();
    switch (m_direction) {
    case UP:
        newBullet->location(tmp_area.site_begin.x+TWIDTH/2, tmp_area.site_begin.y);
        break;
    case DN:
        newBullet->location(tmp_area.site_end.x-TWIDTH/2, tmp_area.site_end.y);
        break;
    case LF:
        newBullet->location(tmp_area.site_begin.x, tmp_area.site_begin.y+THEIGHT/2);
        break;
    case RG:
        newBullet->location(tmp_area.site_end.x, tmp_area.site_end.y-THEIGHT/2);
        break;
    default:
        break;
    }

    m_bullets.append(newBullet);
}

void Tank::shoot()
{
    reloadBullet();
}

void Tank::randshoot()
{
   if(qrand()%5 < 3)
        shoot();
}


void Tank::hook_moveStep()
{
    if(running)
        randTurn();
}

void Tank::randTurn()
{
    static int keep = 0;
    if(++keep < qrand()%10+4 && !m_isTouch)
    {
        return;
    }
    keep = 0;

    switch (qrand()%4) {
    case UP:
        turnDirection(UP);
        break;
    case DN:
        turnDirection(DN);
        break;
    case LF:
        turnDirection(LF);
        break;
    case RG:
        turnDirection(RG);
        break;
    default:
        break;
    }

}

void Tank::updateArea()
{
    m_img->setDrawArea(m_area);
}

void Tank::hook_start()
{
    m_shootTimer->start(m_speed*5/2);
}

void Tank::hook_stop()
{
    m_shootTimer->stop();
}
