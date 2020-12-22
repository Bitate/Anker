#include "MainWindow.hpp"

MainWindow::MainWindow()
    : file_dialog(new QFileDialog(this)),
      open_file_push_button(new QPushButton("Open Folder", this)),
      deck_name_list_widget(new QListWidget(this))
{
    QObject::connect(open_file_push_button, &QPushButton::clicked, this, &MainWindow::response_open_file_push_button_clicked);
    QObject::connect(file_dialog, &QFileDialog::filesSelected, this, &MainWindow::response_files_chosen);
}

void MainWindow::show_main_window()
{
    setWindowTitle("Anker");
    setFixedSize(1024, 666);

    open_file_push_button->setFixedSize(100, 50);
    deck_name_list_widget->setFixedHeight(500);

    QVBoxLayout* vertical_box_layout = new QVBoxLayout();
    vertical_box_layout->addWidget(deck_name_list_widget, 0, Qt::AlignCenter);
    vertical_box_layout->addWidget(open_file_push_button, 0, Qt::AlignCenter);

    QWidget* window = new QWidget();
    window->setLayout(vertical_box_layout);
    setCentralWidget(window);

    show();
}

void MainWindow::set_deck_name_list_widget(const QStringList& new_deck_name_list)
{
    deck_name_list_widget->addItems(new_deck_name_list);

    QListWidgetItem* deck_name = nullptr;
    for(int i = 0; i < deck_name_list_widget->count(); ++i)
    {
        deck_name = deck_name_list_widget->item(i);
        deck_name->setFlags(deck_name->flags() | Qt::ItemIsUserCheckable);
        deck_name->setCheckState(Qt::Unchecked);
    }
    deck_name = nullptr;
}

void MainWindow::response_open_file_push_button_clicked()
{
    file_dialog->open();
}

void MainWindow::response_files_chosen()
{
    // process chosen files
}

void MainWindow::initialize_open_file_window()
{
    // initialize open mode and open path
}

