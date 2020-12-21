#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QListView>
#include <QStyledItemDelegate>
#include <QStringListModel>
#include <QListView>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

public:
    /**
     * Show application's main window.
     */
    void show_main_window();

    /**
     * @brief Set deck names model.
     * @param new_deck_name_list Given string list to be stored in the model.
     */
    void set_deck_name_list_model(const QStringList& new_deck_name_list);
private:
    void initialize_open_file_window();


signals:

public slots:
    void response_open_file_push_button_clicked();
    void response_files_choosen();

private:
    QFileDialog* file_dialog;
    QPushButton* open_file_push_button;

    QStyledItemDelegate* deck_name_list_delegate;
    QStringListModel* deck_name_list_model;
    QListView* deck_name_list_view;
};
