#include "backend.h"
#include<QDebug>
#include <QQmlEngine>

void Backend::sign_inn(QString name)
{
    qDebug() << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" + name;
//    QQmlEngine engine;
//   // engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));
//    engine.setBaseUrl(QUrl::fromLocalFile("myqmlfile.qml"));
//    QQuickView *view = new QQuickView;
//        view->setSource(QUrl(QStringLiteral("qrc:/Home.qml")));
//        view->show();

}

Backend::Backend(QObject *parent) : QObject(parent)
{

}

void Backend::ttt()
{
     qDebug() << "ThhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhT" ;

}
