#ifndef BTHREADTASKITEM_H
#define BTHREADTASKITEM_H

#include <QObject>

namespace Bigo {

    class BThreadTaskItem : public QObject
    {
        Q_OBJECT
    public:
        explicit BThreadTaskItem(QObject *parent = 0);

    public:
    virtual void run() = 0;

    };
}


#endif // BTHREADTASKITEM_H
