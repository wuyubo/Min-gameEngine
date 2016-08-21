#include "btext.h"

namespace Bigo {

    Btext::Btext(QWidget *parent) :
        Bstatic(parent)
    {
        textInit();
    }
    Btext::Btext(QString text, QWidget *parent) :
        Bstatic(parent),
        m_text(text)
    {
        textInit();
    }

    Btext::~Btext()
    {
        delete m_font;
    }

    void Btext::textInit()
    {
        m_font = new QFont("宋体", 20);
        m_id.type = BIDTEXT;
    }

    void Btext::painting(QPainter &painter)
    {
        painter.setFont(*m_font);
        drawText(painter, m_text);
    }

    Bdarea_t Btext::createDrawArea(Bx_t x, By_t y, Bw_t w, Bh_t h)
    {
        createDrawAreaThree(x, y, 0, w, h, 0);
        return m_drawArea;
    }

    void Btext::setText(QString text)
    {
        m_text = text;
    }

    QString Btext::text() const
    {
        return m_text;
    }
//set font
    void Btext::setFontFamily(const QString & family)
    {
        m_font->setFamily(family);
    }

    void Btext::setFontSize(int size)
    {
        m_font->setPointSize(size);
    }

    void Btext::setFontStyle(QFont::Style style)
    {
        m_font->setStyle(style);
    }

    void Btext::setFontWeight(int weight)
    {
        m_font->setWeight(weight);
    }

    void Btext::setFontColor(int r, int g, int b, int a)
    {
        this->setPenColor(r, g, b, a);
    }

    QFont* Btext::font() const
    {
        return m_font;
    }
}

