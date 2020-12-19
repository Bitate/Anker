#include "include/Anker.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Anker anker;

    return app.exec();
}
