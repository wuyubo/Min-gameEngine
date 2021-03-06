#ifndef TDYNCOMMON_H
#define TDYNCOMMON_H
#include "Bobject/bdynamic.h"
#include "Bobject/btypes.h"
#include "gamedata.h"
#include "explope.h"
using namespace Bigo;

class TdynCommon : public Bdynamic
{
    Q_OBJECT
public:
    explicit TdynCommon(QWidget *parent = 0);
    virtual ~TdynCommon();
public:
    virtual Bbool isOutside();
    virtual void setType(TANKTYPE type);
    virtual void updateId();
    virtual void bomb();

public:
    TANKTYPE  m_type;
    Explope *m_bomb;
};

#endif // TDYNCOMMON_H
