#ifndef BDYNACTION_H
#define BDYNACTION_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVector>
#include "Bobject/btypes.h"
#include "Bobject/bobject.h"

namespace Bigo {
    enum DIRECTION{
        UP = 0,
        DN,
        LF,
        RG,
        EN,
    };

    enum SPEED{
        FEST = 250,
        FAST = 500,
        INTE = 750,
        SLOW = 1000,
    };

    enum STEP{
        SMASTEP = 20,
        MEDSTEP = 30,
        BIGSTEP = 40,
        SUPSTEP = 80,
    };

    class BdynObj: public QThread
    {
    Q_OBJECT
    public:
        explicit BdynObj(QWidget *parent = 0);
        virtual ~BdynObj();
        void createId();
    public:
        virtual void run();
        virtual void moveStep();
        virtual void moveAction();
        virtual void moveBack();
        virtual void updateArea();
        virtual Bbool isTouch();
        virtual Bbool doRegion();
        virtual void killed();
        virtual void hook_moveStep();
        virtual void hook_run();
        virtual void hook_start();
        virtual void hook_stop();

    public slots:
        virtual void moving();
    public:
        virtual void turnDirection(DIRECTION d);
        DIRECTION directioin() const;
        virtual void setSpeed(Bint speed);
        Bint speed() const;
        BdynObjId_t getID() const;
        void dynmsleep(int msec);
        Bbool isExist();

    public:
        void startMove();
        void stopMove();

    public:
        bool running;
        DIRECTION m_direction;
        Bint m_step;
        Bint m_speed;
        bool m_isTouch;
        BdynObjId_t m_id;
        Bdarea_t m_area;
        static Bu32 gl_id;
        int m_beyond;
        QTimer *m_timer;

        static QWidget *m_widget;
    };
    typedef QVector<BdynObj *> BdynbObjList;
}


#endif // BDYNACTION_H
