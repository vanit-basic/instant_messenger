#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"
#include <QQmlContext>

int main(int argc, char *argv[] )
{
//bool a = true;
   // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
     //qmlRegisterType<Backend>("io.qt.examples.Engine", 1, 0, "Class");
   // if(a==true){
     Backend * ob = new Backend();



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Class", ob);
   // }
  //  else {
       //   engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));
  //  }
    //if (engine.rootObjects().isEmpty())
       // return -1;

    return app.exec();
}

