#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    initUi();
    initBtn();
}

Widget::~Widget()
{
    delete snakebtn;
    delete exitbtn;
}


void Widget::initUi()
{
    this->resize(WINDOWS_W, WINDOWS_H);
    this->setWindowIcon(QIcon("img/icon.png"));
    this->setWindowTitle("BigoGame");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("img/mainbackground.png").scaled(this->size())));
    this->setPalette(palette);
}

void Widget::initBtn()
{
    snakebtn = new QPushButton(this);
    snakebtn->setIcon(QIcon("img/snakebtn.png"));
    snakebtn->setIconSize(QSize(250,200));
    snakebtn->setGeometry(QRect(170,200,270,210));
    snakebtn->setFlat(true);

    exitbtn = new QPushButton(this);
    exitbtn->setIcon(QIcon("img/exit.png"));
    exitbtn->setIconSize(QSize(60,60));
    exitbtn->setGeometry(QRect(900,20,70, 70));
    exitbtn->setFlat(true);


    tankbtn = new QPushButton(this);
    tankbtn->setIcon(QIcon("img/tankbtn.png"));
    tankbtn->setIconSize(QSize(250,200));
    tankbtn->setGeometry(QRect(570,200,270,210));
    tankbtn->setFlat(true);
    connect(snakebtn, SIGNAL(clicked()), this, SLOT(snaket_btn_clicked()));
    connect(exitbtn, SIGNAL(clicked()), this, SLOT(exit_btn_clicked()));
    connect(tankbtn, SIGNAL(clicked()), this, SLOT(tank_btn_clicked()));
}


void Widget::snaket_btn_clicked()
{
//    snakegame = new SnakeGame(this);
//    snakegame->show();
}
void Widget::exit_btn_clicked()
{
    delete this;
    exit(0);
}
void Widget::tank_btn_clicked()
{
    tankgame = new TankWidget(this);
    tankgame->show();
}
