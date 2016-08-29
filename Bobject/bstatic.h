#ifndef BSTATIC_H
#define BSTATIC_H

#include "Bobject/bobject.h"
#include "Bobject/btypes.h"
#include "Bobject/bglobalobjs.h"
namespace Bigo {

    class Bstatic : public Bobject
    {
        Q_OBJECT
    public:
        explicit Bstatic(QWidget *parent = 0);
        virtual ~Bstatic();
        void show();
        void disappeared();
        virtual void killed();

    signals:

    public slots:

    };
}


#endif // BSTATIC_H
