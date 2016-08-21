#include "tbrick.h"

Tbrick::Tbrick(QWidget *parent) :
    Bimage(parent)
{
    setPath("img/tank/brick1.png");
}

void Tbrick::bomb()
{
    m_bomb = new Explope(this);
    m_bomb->location(drawArea().site_begin.x, drawArea().site_begin.y,
                  drawArea().site_end.x-drawArea().site_begin.x);
}
