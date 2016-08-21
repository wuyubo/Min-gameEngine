#include "tbrick.h"

Tbrick::Tbrick(QWidget *parent) :
    Bimage(parent)
{
    setBrickType(0);
}

void Tbrick::setBrickType(int type)
{
    m_type = type;
    m_id.remain = type;
    initSrc();
}

void Tbrick::initSrc()
{
    switch (m_type) {
    case 0:
        setPath("img/tank/brick1.png");
        break;
    case 1:
        setPath("img/tank/brick2.png");
        break;
    default:
        break;
    }
}

void Tbrick::location(int x, int y)
{
    this->createDrawArea(x, y, 56, 29);
}
