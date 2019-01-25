#include "page1.h"
#include "page2.h"
#include "ui_page1.h"
#include <QPropertyAnimation>
#include <QScreen>
#include <QDebug>
Page1::Page1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Page1)
{
    ui->setupUi(this);
        QScreen *screen = QApplication::screens().at(0);
        largh=screen->availableSize().width();
        alt  =screen->availableSize().height();
        this->resize(largh,alt);

        fb->setObjectName("fb");
        ins->setObjectName("ins");
        go->setObjectName("go");
    //    connect(fb,SIGNAL(pressed()),this,SLOT(SignUpWithButtonsPressed()));
    //    connect(tw,SIGNAL(pressed()),this,SLOT(SignUpWithButtonsPressed()));
    //    connect(go,SIGNAL(pressed()),this,SLOT(SignUpWithButtonsPressed()));
        QPixmap bkgnd(":/img/51062817_2189626127969158_7173693744896540672_n.png");
            bkgnd = bkgnd.scaled(screen->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Background, bkgnd);
            this->setPalette(palette);


}

Page1::~Page1()
{
    delete ui;
}
void Page1::AddButtonProp(QPushButton * btn){
    btn->setParent(widget);
    btn->show();
    if(btn->objectName() == "fb"){
        btn->setGeometry(12,10,60,41);
        btn->setStyleSheet("border-image: url(:/img/facebook.png)");
    }
    else if (btn->objectName() == "ins"){
        btn->setGeometry(96,10,60,41);
        btn->setStyleSheet("border-image: url(:/img/twiter.png)");
    }
    else if (btn->objectName() == "go"){
        btn->setGeometry(180,10,60,41);
        btn->setStyleSheet("border-image: url(:/img/g+.png)");
    }
}


void Page1::on_pushButton_6_clicked()
{
    if(!btnIsChecked){
        QPropertyAnimation* anim = new QPropertyAnimation(widget,"geometry");
        anim->setDuration(300);
        anim->setEasingCurve(QEasingCurve::Linear);
        anim->setEndValue(QRectF((largh-50)/2,alt,0,0));
        anim->start();
        btnIsChecked = true;
    }
    else{
        widget->setParent(this);
        AddButtonProp(fb);
        AddButtonProp(ins);
        AddButtonProp(go);
        widget->resize(50,50);
        widget->setGeometry((largh-50)/2,alt,0,0);
        widget->setStyleSheet("background-color:gray;border-radius:15px");
        widget->show();
        QPropertyAnimation* anim = new QPropertyAnimation(widget,"geometry");
        anim->setDuration(300);
        anim->setEasingCurve(QEasingCurve::Linear);
        anim->setEndValue(QRectF(ui->pushButton_6->x(),ui->pushButton_6->y()+ui->pushButton_6->height()+15,262,61));
        anim->start();
        btnIsChecked = false;
    }

}
void Page1::SignUpWithButtonsPressed()
{
    QPushButton * btn = (QPushButton*)sender();
    btn->setStyleSheet("border-color:white");
}




void Page1::on_pushButton_9_clicked()
{
    page2* p2 = new page2();
    p2->show();
    //hide();
}
