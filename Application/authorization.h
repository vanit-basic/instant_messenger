#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>

class Authorization : public QObject
{
    Q_OBJECT
public:
    explicit Authorization(QObject *parent = nullptr);

    ///////////////////////////////////////////////////////////Sign_in
    Q_INVOKABLE void Sign_in_clicked(QString){} //////QJson
    Q_INVOKABLE void Facebook_clicked(){}
    Q_INVOKABLE void Instagram_clicked(){}
    Q_INVOKABLE void Google_clicked(){}

    ///////////////////////////////////////////////////////////Sign_up
    Q_INVOKABLE void Submit_sign_up_clicked(QString){}  /////QJson

    ///////////////////////////////////////////forgot_password
    Q_INVOKABLE void Mail_request(QString){}
    Q_INVOKABLE void Confirm_code(QString){}
    Q_INVOKABLE void Submit_new_password(QString){}

signals:

    ////////////////////////////Sign_in
    void invalid_user();

    ////////////////////////////Sign_up
    void invalid_name();
    void invalid_surname();
    void invalid_email();
    void invalid_birth_date();
    void invalid_password();

    void connection_lost();

    ///////////////////////////////////////////forgot_password
    void invalid_code();

public slots:

private:

    //////////////////////////////////////Sign_up
    bool isvalid_name(QString);
    bool isvalid_surname(QString);
    bool isvalid_email(QString);
    bool isvalid_birth_date(QString);
    bool isvalid_password(QString);
};

#endif // AUTHORIZATION_H
