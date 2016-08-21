#include "bdynobj.h"

namespace Bigo {

    Bu32 BdynObj::gl_id = 1;
    QWidget *BdynObj::m_widget = NULL;
    BdynObj::BdynObj(QWidget *parent):
        QThread(parent),
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
    }


    BdynObj::~BdynObj()
    {
        while(running)
            stopMove();
        delete m_timer;
    }

    void BdynObj::createId()
    {
        m_id.id = gl_id++;
        m_id.fofoe = FRI;
        m_id.type = 0;
        m_id.remain = 0;
        m_id.exist = true;
    }

    void BdynObj::run()
    {
        while(running)
        {
            moving();
            msleep(m_speed);
            hook_run();
        }
    }

    void BdynObj::moving()
    { 
        moveStep();
    }

    void BdynObj::moveStep()
    {
        moveAction();
        isTouch();
        updateArea();
        hook_moveStep();
        m_widget->update();

    }

    void BdynObj::moveAction()
    {
        switch (m_direction) {
        case UP:
            m_area.site_begin.y -= m_step;
            m_area.site_end.y -= m_step;
            break;
        case DN:
            m_area.site_begin.y += m_step;
            m_area.site_end.y += m_step;
            break;
        case LF:
            m_area.site_begin.x -= m_step;
            m_area.site_end.x -= m_step;
            break;
        case RG:
            m_area.site_begin.x += m_step;
            m_area.site_end.x += m_step;
            break;
        default:
            break;
        }
    }

    void BdynObj::moveBack()
    {
        switch (m_direction) {
        case UP:
            m_area.site_begin.y += m_beyond;
            m_area.site_end.y += m_beyond;
            break;
        case DN:
            m_area.site_begin.y -= m_beyond;
            m_area.site_end.y -= m_beyond;
            break;
        case LF:
            m_area.site_begin.x += m_beyond;
            m_area.site_end.x += m_beyond;
            break;
        case RG:
            m_area.site_begin.x -= m_beyond;
            m_area.site_end.x -= m_beyond;
            break;
        default:
            break;
        }
        m_beyond = 0;
        updateArea();
    }

    void BdynObj::updateArea()
    {

    }

    Bbool BdynObj::isTouch()
    {    
        return m_isTouch;
    }


    Bbool BdynObj::doRegion()
    {
        return false;
    }

    void BdynObj::killed()
    {
        stopMove();
        delete this;
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
        running = true;
//        this->start();
        m_timer->start(m_speed);
        hook_start();

    }

    void BdynObj::stopMove()
    {
        running = false;
        m_timer->stop();
//        while(isRunning());
        hook_stop();
    }

    BdynObjId_t BdynObj::getID() const
    {
        return m_id;
    }

    void BdynObj::dynmsleep(int msec)
    {
        sleep(msec);
    }
    Bbool BdynObj::isExist()
    {
        return m_id.exist;
    }
}

