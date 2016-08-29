#include "bdynobj.h"

namespace Bigo {

    Bu32 BdynObj::gl_dyn_id_value = 1;
    QWidget *BdynObj::m_widget = NULL;
    BdynObj::BdynObj(QWidget *parent):
        QObject(parent),
        running(false),
        m_direction(UP),
        m_step(BIGSTEP),
        m_speed(FAST),
        m_isTouch(false),
        m_beyond(0)
    {
        m_widget = parent;
        createId();
        m_timer = new QTimer(m_widget);
        connect(m_timer,SIGNAL(timeout()), this, SLOT(moving()));
        connect(this,SIGNAL(evt_kill_myself()),this,SLOT(kill_myself()));
        connect(this, SIGNAL(evt_release()), this, SLOT(release_myslef()));
        m_busy = false;
    }


    BdynObj::~BdynObj()
    {
        disconnect(m_timer,SIGNAL(timeout()), this, SLOT(moving()));
        disconnect(this,SIGNAL(evt_kill_myself()),this,SLOT(kill_myself()));
        disconnect(this, SIGNAL(evt_release()), this, SLOT(release_myslef()));

        delete m_timer;
    }

    void BdynObj::createId()
    {
        m_id.id = gl_dyn_id_value++;
        m_id.fofoe = FRI;
        m_id.type = 0;
        m_id.remain = 0;
        m_id.exist = true;
    }

    void BdynObj::run()
    {
        moveStep();
        hook_run();
    }

    void BdynObj::moving()
    { 
//        lock();
        if(m_busy) return;
        if(running)
        {
            emit evt_send_to_thread(this);
        }
        else
        {
            m_timer->stop();
            emit release();
        }
//        unlock();
    }

    void BdynObj::moveStep()
    {
        moveAction();
        isTouch();
        updateArea();
        m_widget->update();
        hook_moveStep();
    }


    void BdynObj::release()
    {
        emit evt_release();
    }

    void BdynObj::release_myslef()
    {
        if(isExist()) kill_myself();
        deleteLater();
//        delete this;
    }

    void BdynObj::killed()
    {
        emit evt_kill_myself();
    }
    void BdynObj::hook_moveStep()
    {

    }
    void BdynObj::hook_run()
    {

    }
    void BdynObj::hook_start()
    {

    }
    void BdynObj::hook_stop()
    {

    }

    void BdynObj::turnDirection(DIRECTION d)
    {
        m_direction = d;
    }

    DIRECTION BdynObj::directioin() const
    {
        return m_direction;
    }

    void BdynObj::setSpeed(Bint speed)
    {
        m_speed = speed;
    }

    Bint BdynObj::speed() const
    {
        return m_speed;
    }

    void BdynObj::startMove()
    {
        if(!running)
        {
            running = true;
            m_timer->start(m_speed);
        }
        hook_start();

    }

    void BdynObj::stopMove()
    {
        if(running)
        {
            running = false;
            hook_stop();
        }
    }

    BdynObjId_t BdynObj::getID() const
    {
        return m_id;
    }


    Bbool BdynObj::isExist()
    {
        return m_id.exist;
    }
    void BdynObj::lock()
    {
        m_mutex.lock();
        m_busy = true;
        m_mutex.unlock();
    }

    void BdynObj::unlock()
    {
        m_mutex.lock();
        m_busy = false;
        m_mutex.unlock();
    }
}

