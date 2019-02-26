#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlEngine engineForPic;
        QQmlComponent componet(&engineForPic,
                QUrl(QStringLiteral("qrc:/HomePage.qml")));
       // QObject *object = componet.create();
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
