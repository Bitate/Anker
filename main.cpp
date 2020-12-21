#include "include/Anker.hpp"
#include "include/MainWindow.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Anker anker;

    MainWindow m;

    QStringList s;
    s << "AAA" << "BBB";
    m.set_deck_name_list_model(s);
    m.show_main_window();

    return app.exec();
}
