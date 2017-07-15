#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickView>
#include <QQmlEngine>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    Client client;
    context->setContextProperty("message",&client);
    client.start("127.0.0.1",9999);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    window->setFlags( /*Qt::Dialog |*/ Qt::CustomizeWindowHint | Qt::WindowTitleHint );

    QObject::connect(window,SIGNAL(sendTextToC(QString)),&client,SLOT(getText(QString)));


    return app.exec();
}


