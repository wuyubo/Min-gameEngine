#include "bcleaner.h"
#include "bcleanobj.h"

namespace Bigo {
    BCleaner::BCleaner(QWidget *parent) :
        BCleanObj(parent)
    {
        connect(this, SIGNAL(evt_send_to_thread(BdynObj*)), BglobalObjs::ptEngine(), SLOT(append_new(BdynObj*)));
        emit evt_send_to_thread(this);
//        startMove();
    }

    BCleaner::~BCleaner()
    {
//        stopMove();
        disconnect(this, SIGNAL(evt_send_to_thread(BdynObj*)), BglobalObjs::ptEngine(), SLOT(append_new(BdynObj*)));
    }

    void BCleaner::cleaning()
    {
        BglobalObjs::cleanObjs();
    }

}

