#ifndef BCLEANER_H
#define BCLEANER_H
#include "bdynamic.h"
#include "bglobalobjs.h"
#include "bcleanobj.h"
namespace Bigo {
    class BCleaner : public BCleanObj
    {
        Q_OBJECT
    public:
        explicit BCleaner(QWidget *parent = 0);
        ~BCleaner();

    public:
        virtual void cleaning();

    public slots:



    };
}


#endif // BCLEANER_H
