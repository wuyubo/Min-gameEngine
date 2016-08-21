#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include "gamedata.h"
#include "Bgame/tank/tankwidget.h"
using namespace Bigo;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void initUi();
    void initBtn();
private slots:
    void snaket_btn_clicked();
    void exit_btn_clicked();
    void tank_btn_clicked();
private:
    QPushButton *snakebtn;
    QPushButton *tankbtn;
    QPushButton *exitbtn;
//    SnakeGame *snakegame;
    TankWidget *tankgame;


};

#endif // WIDGET_H
