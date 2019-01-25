#include "page2.h"
#include "ui_page2.h"
#include <QScreen>

page2::page2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::page2)
{
    ui->setupUi(this);
    QScreen *screen = QApplication::screens().at(0);
    largh=screen->availableSize().width();
    alt  =screen->availableSize().height();
    this->resize(largh,alt);
//    QPixmap bkgnd(":/img/mafia.jpg");
//        bkgnd = bkgnd.scaled(screen->size(), Qt::IgnoreAspectRatio);
//        QPalette palette;
//        palette.setBrush(QPalette::Background, bkgnd);
//        this->setPalette(palette);
    QDate date = QDate::currentDate();
        ui->dateEdit->setDate(date);

}

page2::~page2()
{
    delete ui;
}

void page2::on_pushButton_2_clicked()
{
 this->hide();
}
