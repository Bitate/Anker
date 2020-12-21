#include "MainWindow.hpp"

MainWindow::MainWindow()
    : file_dialog(new QFileDialog(this)),
      open_file_push_button(new QPushButton("Open Folder", this)),
      deck_name_list_delegate(new QStyledItemDelegate(this)),
      deck_name_list_model(nullptr),
      deck_name_list_view(new QListView(this))
{
    QObject::connect(open_file_push_button, &QPushButton::clicked, this, &MainWindow::response_open_file_push_button_clicked);
    QObject::connect(file_dialog, &QFileDialog::filesSelected, this, &MainWindow::response_files_choosen);
}

void MainWindow::show_main_window()
{
    setWindowTitle("Anker");
    setFixedSize(1024, 666);

    deck_name_list_view->setModel(deck_name_list_model);
    deck_name_list_view->setItemDelegate(deck_name_list_delegate);

    open_file_push_button->setFixedSize(100, 100);
    setCentralWidget(open_file_push_button);

    show();
}

void MainWindow::set_deck_name_list_model(const QStringList& new_deck_name_list)
{
    deck_name_list_model = new QStringListModel(new_deck_name_list);
}

void MainWindow::response_open_file_push_button_clicked()
{
    file_dialog->open();
}

void MainWindow::response_files_choosen()
{
    // process choosen files
}

void MainWindow::initialize_open_file_window()
{
    // initialize open mode and open path
}

