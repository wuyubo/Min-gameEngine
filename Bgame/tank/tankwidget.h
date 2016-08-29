#ifndef TANKWIDGET_H
#define TANKWIDGET_H

#include <QWidget>
#include "tank.h"
#include "Bobject/brect.h"
#include <QVector>
#include <QIcon>
#include "gamedata.h"
#include "Bobject/bbasewidget.h"
#include <QPushButton>
#include "explope.h"
#include "tbrick.h"
#include "enemymanage.h"
#include "Bobject/bbackglound.h"

class TankWidget : public BbaseWidget
{
    Q_OBJECT
public:
    explicit TankWidget(QWidget *parent = 0);
    ~TankWidget();
    void init();
    void initBtn();
public:
    Tank* createTank(TANKTYPE type);
signals:


public slots:
     void startClicked();
     void exitClicked();
     void upClicked();
     void downClicked();
     void leftClicked();
     void rightClicked();

private:
    BBackglound *m_bg;
    TankTeamp tankteams;
    Tank *me_army;
    QPushButton *startbtn;
    QPushButton *exitbtn;
    QPushButton *upbtn;
    QPushButton *downbtn;
    QPushButton *leftbtn;
    QPushButton *rightbtn;
    Tbrick *m_brick;
    EnemyManage *m_enManage;
};

#endif // TANKWIDGET_H
