#include "MainWindow.hpp"

MainWindow::MainWindow()
    : open_file_push_button(new QPushButton("Open Files", this)),
      deck_name_list_widget(new QListWidget(this)),
      file_dialog(new QFileDialog(this)),
      is_deck_name_chosen(false)
{
    initialize_open_file_window();
    
    QObject::connect(deck_name_list_widget, &QListWidget::itemChanged, this, &MainWindow::response_deck_item_state_changed);
    QObject::connect(open_file_push_button, &QPushButton::clicked, this, &MainWindow::response_open_file_push_button_clicked);
    QObject::connect(file_dialog, &QFileDialog::urlsSelected, this, &MainWindow::files_chosen);
}

MainWindow::~MainWindow()
{
    delete file_dialog;
    delete open_file_push_button;
    delete deck_name_list_widget;
}

void MainWindow::show_main_window()
{
    setWindowTitle("Anker");
    setFixedSize(330, 660);

    open_file_push_button->setFixedSize(100, 50);
    deck_name_list_widget->setFixedHeight(500);

    QVBoxLayout* vertical_box_layout = new QVBoxLayout();
    vertical_box_layout->addWidget(new QLabel("Please choose one deck to be imported"), 0, Qt::AlignCenter);
    vertical_box_layout->addWidget(deck_name_list_widget, 0, Qt::AlignCenter);
    vertical_box_layout->addWidget(new QLabel("Please click the button below to choose files output from Aboboo"), 0, Qt::AlignCenter);
    vertical_box_layout->addWidget(new QLabel("Tip: press Ctrl+A to choose all files"), 0, Qt::AlignCenter);
    vertical_box_layout->addWidget(open_file_push_button, 0, Qt::AlignCenter);

    QWidget* window = new QWidget();
    window->setLayout(vertical_box_layout);
    setCentralWidget(window);

    show();
}

void MainWindow::set_deck_name_list_widget(const QStringList& new_deck_name_list)
{
    deck_name_list_widget->addItems(new_deck_name_list);

    QListWidgetItem* deck_name;
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

void MainWindow::initialize_open_file_window()
{
    file_dialog->setFileMode(QFileDialog::ExistingFiles);
}

void MainWindow::response_deck_item_state_changed(const QListWidgetItem* changed_deck_item)
{
    if(changed_deck_item->checkState() == Qt::Checked)
    {
        if(is_deck_name_chosen)
        {
            QListWidgetItem* deck_name;
            for(int i = 0; i < deck_name_list_widget->count(); ++i)
            {
                deck_name = deck_name_list_widget->item(i);
                if((deck_name->checkState() == Qt::Checked) && (deck_name != changed_deck_item))
                    deck_name->setCheckState(Qt::Unchecked);
            }
        }
        is_deck_name_chosen = true;
    }
    else
    {
        is_deck_name_chosen = false;
    }

    emit deck_item_state_changed(changed_deck_item);
}

