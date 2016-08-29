#ifndef BTHREADOBJECT_H
#define BTHREADOBJECT_H

#include <QObject>
#include "Bobject/bdynobj.h"
#include "bthreadtaskitem.h"

namespace Bigo {

    class BThreadObject : public QObject
    {
        Q_OBJECT
    public:
        explicit BThreadObject(QObject *parent, BThreadTaskItem * pTaskItem);

    signals:
        void sig_process_finished(BdynObj * data_source);

    public slots:
        void process(BdynObj * data_source, QObject * target);

    private:
        BThreadTaskItem * m_pThreadTaskItem;
    };
}


#endif // BTHREADOBJECT_H
