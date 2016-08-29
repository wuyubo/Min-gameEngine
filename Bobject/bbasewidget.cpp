#include "bbasewidget.h"
#include "assert.h"

namespace Bigo {

    BbaseWidget::BbaseWidget(QWidget *parent) :
        QWidget(parent)
    {
        m_backglound = NULL;
        BglobalObjs::setWidget(this);
        BglobalObjs::create_ptEngine(3, true);
//        m_cleaner = new BCleaner(this);
        connect(this, SIGNAL(evt_delete(Bobject *)), this, SLOT(delete_obj(Bobject*)));
    }

    BbaseWidget::~BbaseWidget()
    {
        BdynObjList_t dynobjlist = BglobalObjs::dynObjList();
        foreach (BdynObj *dobj, dynobjlist) {
            dobj->kill_myself();
            dobj->release_myslef();
        }
        dynobjlist.clear();
        BobjectList_t stcobjlist = BglobalObjs::stcObjList();
        foreach (Bobject *bobj, stcobjlist) {
            bobj->killed();
            bobj->release_myslef();
        }
        stcobjlist.clear();
//        m_cleaner->stopClean();
//        delete m_cleaner;
        BglobalObjs::realease_ptEngine();
        disconnect(this, SIGNAL(evt_delete(Bobject *)), this, SLOT(delete_obj(Bobject*)));
    }

    void BbaseWidget::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        BobjectList_t allobjlist = BglobalObjs::stcObjList();
        if(m_backglound != NULL)
            m_backglound->brush(painter);
        BglobalObjs::paint_begin();
        foreach (Bobject *bobj, allobjlist) {
            if(!bobj->isExist())
            {
//                delete bobj;
                break;
            }
            bobj->brush(painter);
        }
        BglobalObjs::paint_end();

        BglobalObjs::dealfinished();

    }

    void BbaseWidget::delete_obj(Bobject *bobj)
    {
//        bobj->release_myslef();
//        delete bobj;
    }

    void BbaseWidget::setbackground(BBackglound *backglound)
    {
        assert(backglound != NULL);
        m_backglound = backglound;

    }
}
