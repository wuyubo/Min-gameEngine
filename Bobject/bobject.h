#ifndef BOBJECT_H
#define BOBJECT_H

#include <QWidget>
#include "Bobject/btypes.h"
#include <QPainter>
#include <QPen>
#include <QMap>
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
        virtual void killed()=0;
        virtual Bbool isExist();
        void release();
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
    public slots:
        virtual void release_myslef();
    signals:
        void evt_release();
    public:
        Bdarea_t m_drawArea;
        QPen *m_pen;
        OBJSTATE m_state;
        BObjId_t m_id;
        static Bu32 gl_obj_id_value;

    };
    typedef QVector<Bobject *> BobjectLists;
    typedef QMap<BObjId_t *, Bobject*> BobjectMap_t;
    typedef QList<Bobject *> BobjectList_t;
}
#endif //BOBJECT_H
