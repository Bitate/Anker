#include "include/Anker.hpp"
#include "include/MainWindow.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Anker anker;

    anker.show_main_window();

    return app.exec();
}
