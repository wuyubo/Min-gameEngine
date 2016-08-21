#include "bline.h"

namespace Bigo {
    Bline::Bline(QWidget *parent) :
        Bstatic(parent)
    {
        m_id.type = BIDLINE;
    }

    void Bline::painting(QPainter &painter)
    {
        drawLine(painter);
    }
}

