#include "tank.h"

int Tank::enarmy_count = 0;
int Tank::mearmy_count = 0;

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
    delete m_shootTimer;

    switch (m_type) {
    case MEARMY:
        mearmy_count--;
        break;
    case ENARMY:
        enarmy_count--;
        break;
    default:
        break;
    }
//    m_img->disappeared();
//    delete m_img;
}

void Tank::tankInit()
{
    m_id.type = IDTANK;
    m_img->m_id.state = BIDDYNAMI;
    m_img->m_id.dynId = &m_id;
    m_shootTimer = new QTimer(m_widget);
    connect(m_shootTimer,SIGNAL(timeout()), this, SLOT(randshoot()));
    src_Init();
    m_shootInterval = 0;
}

void Tank::setup()
{

    int bx;
    switch (m_type) {
    case MEARMY:
        turnDirection(UP);
        creatDrawArea(TBIGX_BG+TWIND_BG/2-TWIDTH/2, TBIGY_BG+THEIG_BG-THEIGHT, TWIDTH, THEIGHT);
        mearmy_count++;
        break;
    case ENARMY:
        turnDirection(DN);
        bx = (qrand()+m_id.id)%4;
        if(bx == 3)
            bx =(TWIND_BG/3)*bx - TWIDTH;
        else bx =(TWIND_BG/3)*bx;
        creatDrawArea(TBIGX_BG+bx, TBIGY_BG, TWIDTH, THEIGHT);
        this->startMove();
        enarmy_count++;
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
   if(BglobalObjs::Brand(10) < 4)
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
    int rand = BglobalObjs::Brand(10);
    keep ++;
    if(keep < rand+4 && !m_isTouch)
    {
        return;
    }
    keep = 0;

    switch (BglobalObjs::Brand(4)) {
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

void Tank::hook_kill_myself()
{
    m_shootTimer->stop();
    disconnect(m_shootTimer,SIGNAL(timeout()), this, SLOT(randshoot()));
    m_img->killed();
}


Bbool Tank::ignoreCrash(Bobject *bobj)
{
    if(bobj->m_id.state == BIDDYNAMI &&
            bobj->m_id.dynId->type == IDBULL)
        return true;
    return false;
}

int Tank::getEnarmyCount()
{
    return enarmy_count;
}

int Tank::getMearmyCount()
{
    return mearmy_count;
}
