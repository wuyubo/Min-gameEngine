#include "bthreadobject.h"
#include <assert.h>
namespace Bigo {
    BThreadObject::BThreadObject(QObject *parent, BThreadTaskItem * pTaskItem) :
        QObject(parent),
        m_pThreadTaskItem(pTaskItem)
    {
    }

    void BThreadObject::process(BdynObj *data_source, QObject *target)
    {
        if (target==this)
        {
            if(data_source != NULL)
            {
                data_source->run();
            }
            else{
                assert(m_pThreadTaskItem!=NULL);
                m_pThreadTaskItem->run();
            }
            emit sig_process_finished(data_source);
        }
    }
}
