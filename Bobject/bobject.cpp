#include "Bobject/bobject.h"

namespace Bigo {

    Bobject::Bobject(QWidget *parent):
        QWidget(parent)
    {
        resize(parent->size());
        objInit();
    }

    Bobject::Bobject(const Bdarea_t &area, QWidget *parent):
        QWidget(parent),
        m_drawArea(area)
    {
        resize(parent->size());
        objInit();
    }

    Bobject::~Bobject()
    {
        objRelease();
    }

    void Bobject::objInit()
    {
        this->hide();
        m_pen = new QPen(Qt::black, 1, Qt::SolidLine);
        m_state = EXIST;
        createId();
    }

    void Bobject::objRelease()
    {
        delete m_pen;
    }

    void Bobject::createId()
    {
        m_id.id = 0;
        m_id.state = BIDSTATIC;
        m_id.type = BIDUNKW;
        m_id.offset = 0;
        m_id.dynId = NULL;
        m_id.remain2 = 0;
        m_id.exist = true;
    }

    void Bobject::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setPen(*m_pen);
        painting(painter);
    }

    void Bobject::painting(QPainter &painter)
    {
        painter;
    }
    void Bobject::brush(QPainter &painter)
    {
        painter.setPen(*m_pen);
        painting(painter);
    }

    void Bobject::killed()
    {
        m_state = DISAP;
        m_id.exist = false;
//        delete this;
    }
    Bbool Bobject::isExist()
    {
        return m_id.exist;
    }

    Bdarea_t Bobject::createDrawArea(Bx_t x, By_t y, Bw_t w, Bh_t h)
    {
        createDrawAreaThree(x, y, 1, w, h, 1);
        return m_drawArea;
    }

    Bdarea_t Bobject::createDrawAreaThree(Bx_t x, By_t y, Bz_t z, Bw_t w, Bh_t h, Bw_t d)
    {
        m_drawArea.site_begin.x = x;
        m_drawArea.site_begin.y = y;
        m_drawArea.site_end.x = x+w;
        m_drawArea.site_end.y = y+h;
        m_drawArea.site_begin.z = z;
        m_drawArea.site_end.z = z+d;
        return m_drawArea;
    }

    void Bobject::setDrawArea(Bdarea_t &darea)
    {
        m_drawArea = darea;
    }

    Bdarea_t Bobject::drawArea()const
    {
        return m_drawArea;
    }

//set pen style
    void Bobject::setPenColor(int r, int g, int b, int a)
    {
        m_pen->setColor(QColor(r, g, b, a));
    }

    void Bobject::setColor(int r, int g, int b, int a)
    {
        setPenColor(r, g, b, a);
    }


    void Bobject::setPenWidth(int w)
    {
        m_pen->setWidth(w);
    }

    void Bobject::setPenStyte(Qt::PenStyle style)
    {
        m_pen->setStyle(style);
    }

//draw functions
    void Bobject::drawRectH(QPainter &painter)
    {
        painter.drawRect(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                m_drawArea.site_end.x, m_drawArea.site_end.y));
    }

    void Bobject::drawRectS(QPainter &painter)
    {
        painter.setBrush(QBrush(m_pen->color()));
        painter.drawRect(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                m_drawArea.site_end.x, m_drawArea.site_end.y));
        painter.setPen(*m_pen);
    }

    void Bobject::drawEllipseH(QPainter &painter)
    {
        painter.drawEllipse(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                   m_drawArea.site_end.x-m_drawArea.site_begin.x,
                                   m_drawArea.site_end.y-m_drawArea.site_begin.y));
    }

    void Bobject::drawEllipseS(QPainter &painter)
    {
        painter.setBrush(QBrush(m_pen->color()));
        painter.drawEllipse(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                   m_drawArea.site_end.x-m_drawArea.site_begin.x,
                                   m_drawArea.site_end.y-m_drawArea.site_begin.y));
         painter.setPen(*m_pen);
    }

    void Bobject::drawLine(QPainter &painter)
    {
        painter.drawLine(QPoint(m_drawArea.site_begin.x, m_drawArea.site_begin.y),
                         QPoint(m_drawArea.site_end.x, m_drawArea.site_end.y));
    }

    void Bobject::drawPoint(QPainter &painter)
    {
        painter.drawPoint(m_drawArea.site_begin.x, m_drawArea.site_end.y);
    }

    void Bobject::drawImage(QPainter &painter, QString path)
    {
         painter.drawImage(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                  m_drawArea.site_end.x-m_drawArea.site_begin.x,
                                  m_drawArea.site_end.y-m_drawArea.site_begin.y),
                           QImage(path));
    }

    void Bobject::drawText(QPainter &painter, QString text)
    {
        painter.drawText(QRectF(m_drawArea.site_begin.x, m_drawArea.site_begin.y,
                                m_drawArea.site_end.x, m_drawArea.site_end.y),
                         Qt::AlignCenter,
                         text);
    }
}
