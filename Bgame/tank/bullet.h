#ifndef BULLET_H
#define BULLET_H
#include <QVector>
#include "Bobject/bdynamic.h"
#include "Bobject/bellipse.h"
#include "Bobject/btypes.h"
#include "tdyncommon.h"
#include "gamedata.h"
#include "Bobject/bglobalobjs.h"
#include "explope.h"
using namespace Bigo;

#define BR 3

class Bullet : public TdynCommon
{
    Q_OBJECT
public:
    friend class Tank;
    explicit Bullet(QWidget *parent = 0);
    explicit Bullet(TANKTYPE type, DIRECTION d, QWidget *parent = 0);
    ~Bullet();
    void bulletInit();

public:
    void location(int x, int y);
    void dealCrash(Bobject * target);
    void dealOutside();
    void updateArea();
    void hook_moveStep();
    Bbool ignoreCrash(Bobject *bobj);

private:
    Bellipse* m_ellipse;

    int m_r;
};
typedef QVector<Bullet *> BulletClip;

#endif // BULLET_H
