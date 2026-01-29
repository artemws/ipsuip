/** Made by I'm Pancake **/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "functions.h"
#include "gui/MainWindowController.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    // Регистрируем C++ классы для использования в QML
    MainWindowController controller;
    engine.rootContext()->setContextProperty("mainController", &controller);
    
    // Загружаем основной QML файл
    const QUrl url( "qrc:/Ipsuip/qml/MainWindow.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
