#include "enemymanage.h"

EnemyManage::EnemyManage(QWidget *parent) :
    QObject(parent),
    m_tankCount(20),
    m_widget(parent)
{
    m_createTimer = new QTimer(parent);
    connect(m_createTimer, SIGNAL(timeout()),this, SLOT(createTank()));
    m_createTimer->start(1000);
    m_times = 7;
}

EnemyManage::~EnemyManage()
{
    m_createTimer->stop();
    delete m_createTimer;
}

void EnemyManage::setCount(int count)
{
    m_tankCount = count;
}

void EnemyManage::createTank()
{
    if(Tank::getEnarmyCount() < MAXENTCOUNT
            && m_tankCount > 0)
    {
        m_times --;
        if(m_times == 0)
        {
            new Tank(ENARMY, m_widget);
            m_tankCount--;
            m_times = 7;
        }
    }
    if(m_tankCount == 0 && Tank::getEnarmyCount() == 0)
        m_createTimer->stop();
}
