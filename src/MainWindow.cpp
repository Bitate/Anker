#include "MainWindow.hpp"

MainWindow::MainWindow()
    : file_dialog(new QFileDialog()), open_file_push_button(new QPushButton()),
      deck_names_tree_view(new QListView())
{

}

void MainWindow::show_main_window()
{


    setCentralWidget(deck_names_tree_view);

    setWindowTitle("Anker");

    show();
}
