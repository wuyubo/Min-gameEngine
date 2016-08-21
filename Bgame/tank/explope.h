#ifndef EXPLOPE_H
#define EXPLOPE_H

#include "Bobject/bimage.h"
#include "Bobject/bdynamic.h"
using namespace Bigo;
class Explope : public Bdynamic
{
    Q_OBJECT
public:
    explicit Explope(QWidget *parent = 0);
    ~Explope();

public:
    void moveAction();
    Bbool isTouch();
    void location(int x, int y, int r);
    void setImgPath(QString path);
    void updateArea();

private:
    Bimage *m_img;
    QString m_imgpath;
    int m_time;

};

#endif // EXPLOPE_H
