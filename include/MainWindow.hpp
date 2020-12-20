#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QListView>
#include <QStyledItemDelegate>

// forward declaration
class AnkiDeckNamesModel;

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
    QStyledItemDelegate* styled_item_delegate;

};

class AnkiDeckNamesModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    AnkiDeckNamesModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


};
