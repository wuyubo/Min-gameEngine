#ifndef ENEMYMANAGE_H
#define ENEMYMANAGE_H

#include <QObject>
#include <QTimer>
#include "tank.h"

#define MAXENTCOUNT 5
class EnemyManage : public QObject
{
    Q_OBJECT
public:
    explicit EnemyManage(QWidget *parent = 0);
    ~EnemyManage();
    void setCount(int count);
public slots:
    void createTank();

private:
    int m_tankCount;
    QTimer *m_createTimer;
    QWidget *m_widget;
    int m_times;
};

#endif // ENEMYMANAGE_H
