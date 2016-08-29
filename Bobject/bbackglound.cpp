#include "bbackglound.h"

namespace Bigo {
    BBackglound::BBackglound(QWidget *parent) :
        Bobject(parent)
    {
        m_id.state = BIDBACKGL;
        m_id.type = BIDBACKGL;
    }

    void BBackglound::painting(QPainter &painter)
    {
        drawRectS(painter);
    }
    void BBackglound::killed()
    {
        delete this;
    }

}
