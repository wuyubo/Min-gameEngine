#ifndef BOBJECT_H
#define BOBJECT_H

#include <QWidget>
#include "Bobject/btypes.h"
#include <QPainter>
#include <QPen>

namespace Ui {
class Bobject;
}

namespace Bigo {

    class Bobject: public QWidget
    {
        Q_OBJECT
    public:
        explicit Bobject(QWidget *parent = 0);
        explicit Bobject(const Bdarea_t &area, QWidget *parent = 0);
        virtual ~Bobject();

    protected:
        void objInit();
        void objRelease();
        void createId();
    public: //virtual functions
        virtual void paintEvent(QPaintEvent *);
        virtual void painting(QPainter &painter);
        virtual void brush(QPainter &painter);
        virtual void killed();
        virtual Bbool isExist();
    public: //area functions
        virtual Bdarea_t createDrawArea(Bx_t x, By_t y, Bw_t w, Bh_t h);
        virtual Bdarea_t createDrawAreaThree(Bx_t x, By_t y, Bz_t z, Bw_t w, Bh_t h, Bw_t d);
        void setDrawArea(Bdarea_t &darea);
        Bdarea_t drawArea() const;
    public: //pen functions
        void setPenColor(int r, int g, int b, int a = 255);
        void setColor(int r, int g, int b, int a = 255);
        void setPenWidth(int w);
        void setPenStyte(Qt::PenStyle style);
    public: //draw functions
        void drawRectH(QPainter &painter);
        void drawRectS(QPainter &painter);
        void drawEllipseH(QPainter &painter);
        void drawEllipseS(QPainter &painter);
        void drawLine(QPainter &painter);
        void drawPoint(QPainter &painter);
        void drawImage(QPainter &painter, QString path);
        void drawText(QPainter &painter, QString text);
    public:
        Bdarea_t m_drawArea;
        QPen *m_pen;
        OBJSTATE m_state;
        BObjId_t m_id;

    };
    typedef QVector<Bobject *> BobjectLists;
}
#endif //BOBJECT_H
