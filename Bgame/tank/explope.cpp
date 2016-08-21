#include "explope.h"

Explope::Explope(QWidget *parent) :
    Bdynamic(parent),
    m_time(4),
    m_imgpath("img/tank/bomb.png")
{
    m_img = new Bimage(parent);
    m_img->setPath(m_imgpath);
    m_speed = 200;
}

Explope::~Explope()
{
    delete m_img;
}

void Explope::moveAction()
{
    static int times = 0;

    m_area.site_begin.x -= 5;
    m_area.site_begin.y -= 5;
    m_area.site_end.x += 5;
    m_area.site_end.y += 5;

    if(times++ > m_time)
        killed();
}

Bbool Explope::isTouch()
{
    return false;
}

void Explope::location(int x, int y, int r)
{
    m_area = m_img->createDrawAreaThree(x, y, 0, r, r, 0);
    startMove();
}

void Explope::setImgPath(QString path)
{
    m_imgpath = path;
    m_img->setPath(m_imgpath);
}

void Explope::updateArea()
{
    m_img->setDrawArea(m_area);
}

void Explope::bomb(int x, int y, int r)
{
    Explope *m_bomb = new Explope(m_widget);
    m_bomb->location(x, y, r);
}
