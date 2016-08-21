#include "bimage.h"

namespace Bigo {

    Bimage::Bimage(QWidget *parent) :
        Bstatic(parent)
    {
        m_id.type = BIDIMGE;
    }


    Bimage::Bimage(QString path, QWidget *parent) :
        Bstatic(parent),
        m_path(path)
    {
        m_id.type = BIDIMGE;
    }

    void Bimage::painting(QPainter &painter)
    {
        drawImage(painter, m_path);
    }

    void Bimage::setPath(QString path)
    {
        m_path = path;
    }

    QString Bimage::imgPath()const
    {
        return m_path;
    }

}
