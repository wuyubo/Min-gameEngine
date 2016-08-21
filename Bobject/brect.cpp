#include "brect.h"

namespace Bigo {
    Brect::Brect(QWidget *parent) :
        Bstatic(parent)
    {
        m_style = RHOLLOW;
        m_id.type = BIDRECT;
    }
    Brect::Brect(RECTSTYLE style, QWidget *parent):
        Bstatic(parent),
        m_style(style)
    {
        m_id.type = BIDRECT;
    }

    void Brect::painting(QPainter &painter)
    {
        switch (m_style) {
        case RHOLLOW:
            drawRectH(painter);
            break;
        case RSOLID:
            drawRectS(painter);
        default:
            break;
        }

    }

    void Brect::setStyle(RECTSTYLE style)
    {
        m_style = style;
    }

    RECTSTYLE Brect::style()const
    {
        return m_style;
    }
}
