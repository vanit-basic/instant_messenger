#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QObject>

class Sign_in : public QObject
{
    Q_OBJECT
public:
    explicit Sign_in(QObject *parent = nullptr);

    Q_INVOKABLE void Sign_in_clicked(QJsonDocument);
    Q_INVOKABLE void Sign_up_clicked();  //onknown
    Q_INVOKABLE void Forgot_Pass_clicked();
    Q_INVOKABLE void Facebook_clicked();
    Q_INVOKABLE void Instagram_clicked();
    Q_INVOKABLE void Google_clicked();

signals:

    void invalidUser();

public slots:

};

#endif // SIGN_IN_H
