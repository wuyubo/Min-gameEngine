#include "explope.h"

Explope::Explope(QWidget *parent) :
    Bdynamic(parent),
    m_time(3),
    m_imgpath("img/tank/bomb.png")
{
    m_img = new Bimage(parent);
    m_img->setPath(m_imgpath);
    m_speed = FEST;
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
    m_area = m_img->createDrawAreaThree(x-r/2, y-r/2, 0, 2*r, 2*r, 0);
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
