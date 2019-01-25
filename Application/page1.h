#ifndef PAGE1_H
#define PAGE1_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class Page1;
}

class Page1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Page1(QWidget *parent = nullptr);
    ~Page1();

private slots:
    void on_pushButton_6_clicked();
    void SignUpWithButtonsPressed();


    void on_pushButton_9_clicked();

private:
    Ui::Page1 *ui;
    int largh;
    int alt;
    bool btnIsChecked = true;
    QWidget *widget = new QWidget();
    QPushButton* fb = new QPushButton();
    QPushButton* ins = new QPushButton();
    QPushButton* go = new QPushButton();
    void AddButtonProp(QPushButton * btn);
};

#endif // PAGE1_H
