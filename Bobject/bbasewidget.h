#ifndef BBASEWIDGET_H
#define BBASEWIDGET_H

#include <QWidget>
#include <QTimer>
#include "Bobject/bglobalobjs.h"
#include "Bobject/bobject.h"
#include "bcleaner.h"
#include "bbackglound.h"

namespace Bigo {

    class BbaseWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit BbaseWidget(QWidget *parent = 0);
        virtual ~BbaseWidget();
    public:
        virtual void paintEvent(QPaintEvent *);
        void setbackground(BBackglound *backglound);
    public slots:
        void delete_obj(Bobject *bobj);
    signals:
        void evt_delete(Bobject *bobj);
    private:
        BCleaner *m_cleaner;
        BBackglound *m_backglound;
    };
}


#endif // BBASEWIDGET_H
