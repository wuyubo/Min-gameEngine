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
    void bomb();

signals:

public:
    Explope *m_bomb;

};

#endif // TBRICK_H
