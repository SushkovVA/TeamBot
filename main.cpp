#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "messagecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Передача в QML класса логики
    MessageController messageController(nullptr);
    engine.rootContext()->setContextProperty("messageController", &messageController);
    // ====

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
