#ifndef BELLIPSE_H
#define BELLIPSE_H

#include "Bobject/bstatic.h"

namespace Bigo {

    enum ELLIPSESTYLE{
        EHOLLOW,
        ESOLID,
    };
    class Bellipse : public Bstatic
    {
        Q_OBJECT
    public:
        explicit Bellipse(QWidget *parent = 0);
        explicit Bellipse(ELLIPSESTYLE style, QWidget *parent = 0);


    public: //virtual functions
        virtual void painting(QPainter &painter);

    public:
        void setStyle(ELLIPSESTYLE style);
        ELLIPSESTYLE style() const;
    protected:
        ELLIPSESTYLE m_style;
    };
}


#endif // BELLIPSE_H
