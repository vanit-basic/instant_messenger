#ifndef PAGE2_H
#define PAGE2_H

#include <QDialog>

namespace Ui {
class page2;
}

class page2 : public QDialog
{
    Q_OBJECT

public:
    explicit page2(QWidget *parent = nullptr);
    ~page2();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::page2 *ui;
    int largh;
    int alt;
};

#endif // PAGE2_H
