#include "bstatic.h"
namespace Bigo {
    Bstatic::Bstatic(QWidget *parent) :
        Bobject(parent)
    {
        show();
    }

    Bstatic::~Bstatic()
    {
        if(isExist())
            killed();
    }


    void Bstatic::show()
    {
        m_id.exist = true;
        BglobalObjs::stcObjappend(&m_id, this);
    }

    void Bstatic::disappeared()
    {
        BglobalObjs::stcObjremove(&m_id);
        m_id.exist = false;
    }

    void Bstatic::killed()
    {
        if(isExist())
        {
            disappeared();
//            emit evt_release();
        }
    }
}

