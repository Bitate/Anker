#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QGuiApplication>
#include <QQuickItem>
#include <QQuickView>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView view;

    view.setTitle("Anker");
    view.setSource(QUrl("qrc:/qmls/mainWindow.qml"));
    view.show();

    return app.exec();
}
