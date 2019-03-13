#include "backend.h"
#include<QDebug>
#include <QQmlApplicationEngine>
void Backend::sign_inn(QString name)
{
    qDebug() << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" + name;
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));



}

Backend::Backend(QObject *parent) : QObject(parent)
{

}

void Backend::ttt()
{
     qDebug() << "ThhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhT" ;

}
