#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"
#include <QQmlContext>

int main(int argc, char *argv[] )
{
    bool a = true;
     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    //qmlRegisterType<Backend>("io.qt.examples.Engine", 1, 0, "Class");
    // if(a==true){
    Backend * ob = new Backend();

    if(a==true)

        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        else
            engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));


        engine.rootContext()->setContextProperty("Class", ob);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

