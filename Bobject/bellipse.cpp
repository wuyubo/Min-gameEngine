#include "bellipse.h"

namespace Bigo {
    Bellipse::Bellipse(QWidget *parent) :
        Bstatic(parent)
    {
        m_style = EHOLLOW;
        m_id.type = BIDELLI;
    }
    Bellipse::Bellipse(ELLIPSESTYLE style, QWidget *parent) :
        Bstatic(parent),
        m_style(style)
    {
        m_id.type = BIDELLI;
    }


    void Bellipse::painting(QPainter &painter)
    {
        switch (m_style) {
        case EHOLLOW:
            drawEllipseH(painter);
            break;
        case ESOLID:
            drawEllipseS(painter);
        default:
            break;
        }
    }

    void Bellipse::setStyle(ELLIPSESTYLE style)
    {
        m_style = style;
    }

    ELLIPSESTYLE Bellipse::style()const
    {
        return m_style;
    }
}

