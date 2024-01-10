#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ImageFetcher.h"
#include <QtMath>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageFetcher>("com.example", 1, 0, "ImageFetcher");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("file:///C:/Users/arbus/OneDrive/Dokumenty/homework/src/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
