#ifndef BBACKGLOUND_H
#define BBACKGLOUND_H

#include "brect.h"
namespace Bigo {

    class BBackglound : public Bobject
    {
        Q_OBJECT
    public:
        explicit BBackglound(QWidget *parent = 0);
        virtual void painting(QPainter &painter);
        void killed();

    signals:

    public slots:

    };
}


#endif // BBACKGLOUND_H
