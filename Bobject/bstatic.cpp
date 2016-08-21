#include "bstatic.h"
namespace Bigo {
    Bstatic::Bstatic(QWidget *parent) :
        Bobject(parent)
    {
        m_id.id = BglobalObjs::allObjsCount();
        BglobalObjs::allObjsAppend(this);
    }

    Bstatic::~Bstatic()
    {
        BglobalObjs::allObjsremove(m_id.id);
    }

    void Bstatic::killed()
    {
        m_id.exist = false;
    }
}

