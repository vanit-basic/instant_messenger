#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QObject>

class Sign_up : public QObject
{
    Q_OBJECT
public:
    explicit Sign_up(QObject *parent = nullptr);

    Q_INVOKABLE void Submit_clicked(QJsonDocument);

signals:

    void invalid_name();
    void invalid_surname();
    void invalid_email();
    void invalid_birth_date();
    void invalid_password();
    void wrong_password_repetition(); //onknown

public slots:

private:

    bool isvalid_name(QString);
    bool isvalid_surname(QString);
    bool isvalid_email(QString);
    bool isvalid_birth_date(QString);
    bool isvalid_password(QString);
};

#endif // SIGN_UP_H
