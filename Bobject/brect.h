#ifndef BRECT_H
#define BRECT_H

#include <QWidget>
#include "Bobject/bstatic.h"

namespace Bigo {
    enum RECTSTYLE{
        RHOLLOW,
        RSOLID,
    };

    class Brect : public Bstatic
    {
        Q_OBJECT
    public:
        explicit Brect(QWidget *parent = 0);
        explicit Brect(RECTSTYLE style, QWidget *parent = 0);

    public: //virtual functions
        virtual void painting(QPainter &painter);

    public:
        void setStyle(RECTSTYLE style);
        RECTSTYLE style() const;
    protected:
        RECTSTYLE m_style;

    };
}


#endif // BRECT_H
