#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Game.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<Game>("Game.enums", 1, 0, "GameFinishedEnum",
        "Not creatable as it is an enum type.");

    Game game;
    engine.rootContext()->setContextProperty("game", &game);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
