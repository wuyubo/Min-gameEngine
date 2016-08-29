#include "bcleanobj.h"

namespace Bigo {
    BCleanObj::BCleanObj(QWidget *parent) :
        BdynObj(parent)
    {

    }


    void BCleanObj::run()
    {
        while (m_id.exist) {
            cleaning();
        }
    }
    void BCleanObj::stopClean()
    {
        m_id.exist = false;
        cleaning();
    }

    void BCleanObj::moveAction()
    {

    }

    void BCleanObj::moveBack()
    {

    }

    void BCleanObj::updateArea()
    {

    }

    Bbool BCleanObj::isTouch()
    {
        return false;
    }

    Bbool BCleanObj::doRegion()
    {
        return false;;
    }

    void BCleanObj::kill_myself()
    {

    }
}


