#include "include/Anker.hpp"

#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Anker anker;

    // Note: the path is hard-coded,
    // I cannot load it if I use qrc
    // to manage files.
    engine.load("C:/repos/Anker/main.qml");
    engine.rootContext()->setContextProperty("Anker", &anker);
    return app.exec();
}
