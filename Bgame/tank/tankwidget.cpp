#include "tankwidget.h"

TankWidget::TankWidget(QWidget *parent) :
    BbaseWidget(parent)
{
    this->setAutoFillBackground(true);//覆盖父窗口
    init();
    initBtn();
}

TankWidget::~TankWidget()
{
//    Tank *tmptank;
//    int i;
    delete startbtn;
    delete exitbtn;
    delete upbtn;
    delete downbtn;
    delete leftbtn;
    delete rightbtn;
//    delete me_army;

//    for(i = 0; i<tankteams.size(); i++)
//    {
//        tmptank = tankteams[i];
//        tmptank->stopMove();
//        delete tmptank;
//    }
//    tankteams.clear();

}
void TankWidget::init()
{
    this->resize(WINDOWS_W, WINDOWS_H);
    this->setWindowIcon(QIcon("img/icon.png"));
    this->setWindowTitle("坦克大战");
    m_bg_rect = new Brect(this);
    m_bg_rect->createDrawAreaThree(TBIGX_BG,TBIGY_BG, 2, TWIND_BG, THEIG_BG, 0);
    m_bg_rect->setStyle(RSOLID);

    createTank(MEARMY);
    createTank(ENARMY);
    createTank(ENARMY);
    m_brick = new Tbrick(this);
    m_brick->createDrawArea(500, 500, 80, 20);
}



void TankWidget::initBtn()
{
    int startx = TBIGX_BG+TWIND_BG+10, starty = WINDOWS_H*3/5;
    int btnWidth = 60, btnHeight = 40;
    int offset = 10;
    startbtn = new QPushButton("射击",this);
    exitbtn = new QPushButton("退出",this);
    upbtn = new QPushButton(this);
    downbtn = new QPushButton(this);
    leftbtn = new QPushButton(this);
    rightbtn = new QPushButton(this);

    upbtn->setIcon(QIcon("img/snake/up.png"));
    upbtn->setIconSize(QSize(btnWidth,btnHeight));
    downbtn->setIcon(QIcon("img/snake/down.png"));
    downbtn->setIconSize(QSize(btnWidth,btnHeight));
    leftbtn->setIcon(QIcon("img/snake/left.png"));
    leftbtn->setIconSize(QSize(btnWidth,btnHeight));
    rightbtn->setIcon(QIcon("img/snake/right.png"));
    rightbtn->setIconSize(QSize(btnWidth,btnHeight));


    startbtn->setGeometry(QRect(startx+btnWidth+offset,starty+btnHeight+offset,btnWidth, btnHeight));
    exitbtn->setGeometry(QRect(WINDOWS_W-(btnWidth+3*offset),
                               WINDOWS_H-(btnHeight+3*offset),btnWidth*2/3, btnHeight*2/3));

    upbtn->setGeometry(   QRect(startx+btnWidth+offset, starty, btnWidth, btnHeight));
    downbtn->setGeometry( QRect(startx+btnWidth+offset, starty+btnHeight*2+2*offset, btnWidth, btnHeight));
    leftbtn->setGeometry( QRect(startx, starty+btnHeight+offset, btnWidth, btnHeight));
    rightbtn->setGeometry(QRect(startx+btnWidth*2+2*offset, starty+btnHeight+offset, btnWidth, btnHeight));

    connect(this->startbtn, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(this->exitbtn, SIGNAL(clicked()), this, SLOT(exitClicked()));
    connect(this->upbtn, SIGNAL(clicked()), this, SLOT(upClicked()));
    connect(this->downbtn, SIGNAL(clicked()), this, SLOT(downClicked()));
    connect(this->leftbtn, SIGNAL(clicked()), this, SLOT(leftClicked()));
    connect(this->rightbtn, SIGNAL(clicked()), this, SLOT(rightClicked()));

//        level_lb = new  QLabel(this);
//        level_lb->setGeometry(QRect(startx+50, 50, 170, 90));
//        level_lb->setStyleSheet("QLabel{background:rgb(234,71,6);color:white}");
//        level_lb->setText("第一关");
//        level_lb->setFont(QFont("黑体", 40, 40));

//        score_lb = new QLabel(this);
//        score_lb->setGeometry(QRect(startx+50, 140, 170, 90));
//        score_lb->setStyleSheet("QLabel{background:rgb(234,71,6);color:white}");
//        score_lb->setText("本局：0 分");
//        score_lb->setFont(QFont("黑体", 20, 20));
}




Tank *TankWidget::createTank(TANKTYPE type)
{
    Tank *newTank =new Tank(type, this);
    if(type == MEARMY) me_army = newTank;
    else tankteams.append(newTank);
    return newTank;
}


void TankWidget::startClicked()
{
    me_army->shoot();
}

void TankWidget::exitClicked()
{
   delete this;
}

void TankWidget::upClicked()
{
    if(me_army!=NULL)
    {
        if(me_army->directioin() != UP)
            me_army->turnDirection(UP);
        else me_army->moveStep();
    }
}

void TankWidget::downClicked()
{
    if(me_army!=NULL)
    {
        if(me_army->directioin() != DN)
            me_army->turnDirection(DN);
        else me_army->moveStep();
    }
}

void TankWidget::leftClicked()
{
    if(me_army!=NULL)
    {
        if(me_army->directioin() != LF)
            me_army->turnDirection(LF);
        else me_army->moveStep();
    }
}

void TankWidget::rightClicked()
{
    if(me_army!=NULL)
    {
        if(me_army->directioin() != RG)
            me_army->turnDirection(RG);
        else me_army->moveStep();
    }
}
