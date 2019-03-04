#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[] )
{
bool a = true;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    if(a==true){
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
    else {
          engine.load(QUrl(QStringLiteral("qrc:/mainnn.qml")));
    }
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
