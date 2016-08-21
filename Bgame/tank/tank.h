#ifndef TANK_H
#define TANK_H

#include "Bobject/bimage.h"
#include "Bobject/bdynamic.h"
#include "gamedata.h"
#include "Bobject/bglobalobjs.h"
#include "Bgame/tank/bullet.h"
#include "tdyncommon.h"
#include <QVector>
#include <QTimer>
using namespace Bigo;

#define TWIDTH 50
#define THEIGHT 50

class Tank: public TdynCommon
{
Q_OBJECT
public:
    explicit Tank(QWidget *parent = 0);
    explicit Tank(TANKTYPE type, QWidget *parent = 0);
    ~Tank();
    void tankInit();
    void setup();
public:
    void src_Init();
    void turnDirection(DIRECTION d);
    void creatDrawArea(int x, int y, int w, int h);
    void setType(TANKTYPE type);
    void reloadBullet();
    void hook_moveStep();
    void randTurn();
    void hook_start();
    void hook_stop();
    void shoot();
public slots:
    void randshoot();


    void updateArea();
private:
    Bimage *m_img;
    QString m_img_src[5];
    BulletClip m_bullets;
    QTimer *m_shootTimer;
};

typedef QVector<Tank*> TankTeamp;

#endif //TANK_H
