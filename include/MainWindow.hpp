#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QListView>

class MainWindow : public QMainWindow
{
public:
    MainWindow();

public:
    void show_main_window();

private:
    QFileDialog* file_dialog;
    QPushButton* open_file_push_button;
    QListView* deck_names_tree_view;
};
