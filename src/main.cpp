#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("MultiChannelMonitor", "Main");

    qDebug() << "GUI thread:" << QThread::currentThread();
    return app.exec();
}