#include "../include/Anker.hpp"

#include <string>
#include <iostream>

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QGuiApplication>
#include <QQuickItem>
#include <QQuickView>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QMediaPlayer>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    Anker anker;

    auto anki_names = anker.get_deck_names();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app_directory_path", QGuiApplication::applicationDirPath());
    engine.load(QUrl::fromLocalFile(":/qmls/mainWindow.qml"));

    if(engine.rootObjects().isEmpty())
    {
        QMessageBox::warning(nullptr, "Error", "QML engine failed to load QML file");
        return -1;
    }

    std::cout << "Running" << std::endl;

    return app.exec();
}
