#ifndef BDYNACTION_H
#define BDYNACTION_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVector>
#include "Bobject/btypes.h"
#include "Bobject/bobject.h"
#include <QMutex>

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

    class BdynObj: public QObject
    {
    Q_OBJECT
    public:
        explicit BdynObj(QWidget *parent = 0);
        virtual ~BdynObj();
        void createId();
    public:
        virtual void run();
        virtual void moveStep();
        virtual void moveAction() = 0;
        virtual void moveBack() = 0;
        virtual void updateArea() = 0;
        virtual Bbool isTouch() = 0;
        virtual Bbool doRegion() = 0;
        virtual void killed();
        virtual void hook_moveStep();
        virtual void hook_run();
        virtual void hook_start();
        virtual void hook_stop();
        virtual void release();

    public slots:
        virtual void moving();
        virtual void kill_myself() = 0;
        virtual void release_myslef();
    signals:
        void evt_send_to_thread(BdynObj *myself);
        void evt_kill_myself();
        void evt_release();


    public:
        virtual void turnDirection(DIRECTION d);
        DIRECTION directioin() const;
        virtual void setSpeed(Bint speed);
        Bint speed() const;
        BdynObjId_t getID() const;
        Bbool isExist();
        void lock();
        void unlock();

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

        int m_beyond;
        QTimer *m_timer;
        static Bu32 gl_dyn_id_value;

        static QWidget *m_widget;
        QMutex m_mutex;
        Bbool m_busy;
    };
    typedef QMap<BdynObjId_t *, BdynObj*> BdynObjMap_t;
    typedef QList<BdynObj *> BdynObjList_t;
}


#endif // BDYNACTION_H
