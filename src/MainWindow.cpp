#include "MainWindow.hpp"

MainWindow::MainWindow()
    : file_dialog(new QFileDialog()), open_file_push_button(new QPushButton()),
      deck_names_tree_view(new QListView()), styled_item_delegate(new QStyledItemDelegate())
{

}

void MainWindow::show_main_window()
{
    setCentralWidget(deck_names_tree_view);

    setWindowTitle("Anker");

    // styled_item_delegate->setModelData();

    show();
}
