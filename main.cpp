#include "include/Anker.hpp"

#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Anker anker;
    // BUG: can not load qml file from qrc.
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Anker", &anker);
    return app.exec();
}
