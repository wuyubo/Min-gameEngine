#include "bbasewidget.h"

namespace Bigo {

    BbaseWidget::BbaseWidget(QWidget *parent) :
        QWidget(parent)
    {
        m_cleanTimer = new QTimer(this);
        connect(m_cleanTimer,SIGNAL(timeout()), this, SLOT(cleanObjs()));
        m_cleanTimer->start(500);
    }

    BbaseWidget::~BbaseWidget()
    {
        Bobject *temp;
        while (BglobalObjs::dynObjsCount() > 0)
        {
            temp = BglobalObjs::gl_allObjs[0];
            deletObj(temp);
        }
    }

    void BbaseWidget::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        Bobject *temp;
        for(QVector<Bobject*>::Iterator iter = BglobalObjs::gl_allObjs.begin();
            iter != BglobalObjs::gl_allObjs.end(); iter++)
        {
            temp = (Bobject*)*iter;
            temp->brush(painter);
        }
    }

    void BbaseWidget::deletObj(Bobject *bobj)
    {
         BdynObj *tempdyn;
        if(bobj->m_id.state == BIDDYNAMI)
        {
           tempdyn= BglobalObjs::dynObjReflect(bobj);
           tempdyn->killed();
           delete tempdyn;
        }
        else
        {
            bobj->killed();
            delete bobj;
        }
    }

    void BbaseWidget::cleanObjs()
    {
        Bobject *temp;
        BdynObj *tempdyn;
        BdynbObjList dynlist =  BglobalObjs::gl_dynObjs;

        for(QVector<BdynObj*>::Iterator iter = dynlist.begin();
            iter != dynlist.end(); iter++)
        {
            tempdyn = *iter;

            if(!tempdyn->isExist())
            {
                tempdyn->killed();
                delete tempdyn;
            }
        }

        BobjectLists alllist = BglobalObjs::gl_allObjs;
        for(QVector<Bobject*>::Iterator iter = alllist.begin();
            iter != alllist.end(); iter++)
        {
            temp = *iter;
            if(!temp->isExist())
            {
                deletObj(temp);
            }
        }

    }

}
