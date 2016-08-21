#ifndef BLINE_H
#define BLINE_H

#include <QWidget>
#include "Bobject/bstatic.h"

namespace Bigo {

    class Bline : public Bstatic
    {
        Q_OBJECT
    public:
        explicit Bline(QWidget *parent = 0);

    public: //virtual functions
        virtual void painting(QPainter &painter);
    public:
        void setWidth(int width);

    };
}


#endif // BLINE_H
