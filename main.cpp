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
#include <QObject>
#include <QFileDialog>

#include "qtqml.h"

int main(int argc, char *argv[])
{
    qtQML qt;

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("app_directory_path", QApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("qt", &qt);
    engine.load(QUrl::fromLocalFile(":/qmls/mainWindow.qml"));

    return app.exec();
}
