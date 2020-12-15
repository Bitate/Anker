#include "include/Anker.hpp"

#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Anker anker;

    // Hard-coded path
    // TODO: change local file system to use qrc file system to handle resources
    engine.load(QUrl::fromLocalFile("C:/repos/Anker/main.qml"));

    engine.rootContext()->setContextProperty("Anker", &anker);
    return app.exec();
}
