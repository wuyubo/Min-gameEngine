#ifndef BTEXT_H
#define BTEXT_H

#include <QWidget>
#include <QFont>
#include "Bobject/bstatic.h"

namespace Bigo {

    class Btext : public Bstatic
    {
        Q_OBJECT
    public:
        explicit Btext(QWidget *parent = 0);
        explicit Btext(QString text, QWidget *parent = 0);
        ~Btext();
        void textInit();
    public: //virtual functions
        virtual void painting(QPainter &painter);
        virtual Bdarea_t createDrawArea(Bx_t x, By_t y, Bw_t w, Bh_t h);
    public:
        void setText(QString text);
        QString text() const;
    public: //set font functions;
        void setFontFamily(const QString & family);
        void setFontSize(int size);
        void setFontStyle(QFont::Style style);
        void setFontWeight(int weight);
        void setFontColor(int r, int g, int b, int a = 255);
        QFont* font() const;


    protected:
        QString m_text;
        QFont *m_font;
    };
}


#endif // BTEXT_H
