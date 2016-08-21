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
public:
    static void bomb(int x, int y, int r);

private:
    Bimage *m_img;
    int m_time;
    QString m_imgpath;

};

#endif // EXPLOPE_H
