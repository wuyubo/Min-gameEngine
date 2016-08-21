#ifndef BBASEWIDGET_H
#define BBASEWIDGET_H

#include <QWidget>
#include <QTimer>
#include "Bobject/bglobalobjs.h"
#include "Bobject/bobject.h"

namespace Bigo {

    class BbaseWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit BbaseWidget(QWidget *parent = 0);
        virtual ~BbaseWidget();
    public:
        virtual void paintEvent(QPaintEvent *);
        void deletObj(Bobject *bobj);
    protected slots:
        virtual void cleanObjs();

    private:
        QTimer *m_cleanTimer;
    };
}


#endif // BBASEWIDGET_H
