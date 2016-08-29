#ifndef TBRICK_H
#define TBRICK_H
#include "Bobject/bimage.h"
#include "explope.h"
using namespace Bigo;

class Tbrick : public Bimage
{
    Q_OBJECT
public:
    explicit Tbrick(QWidget *parent = 0);
    void setBrickType(int type);
    void initSrc();
    void location(int x, int y);

signals:

private:
    int m_type;

};

#endif // TBRICK_H
