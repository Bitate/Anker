#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // Lifetime management
public:
    MainWindow();
    ~MainWindow();

public:
    /**
     * @brief  Show anker's main window.
     */
    void show_main_window();

    /**
     * @brief  Set deck names inside a QListWidget object.
     * @param  new_deck_name_list Given string list to be stored in the model.
     */
    void set_deck_name_list_widget(const QStringList& new_deck_name_list);

private:
    /**
     * @brief  Initialize file dialog settings.
     */
    void initialize_open_file_window();

signals:
    /**
     * @brief  A signal denotes deck item has been chosen by user in main window.
     * @param  changed_deck_item  Changed deck item.
     */
    void deck_item_state_changed(const QListWidgetItem *changed_deck_item);

    /**
     * @brief  Wrapper signal for QFileDialog::urlsSelected.
     * @param  new_file_urls  New file urls selected by user.
     */
    void files_chosen(const QList<QUrl>& new_file_urls);

public slots:
    /**
     * @brief  Handle user's selection of front end. If user check a new item, 
     *         this will uncheck the older one to ensure exclusive selection.
     * @param  changed_deck_item  Changed deck item.
     */
    void response_deck_item_state_changed(const QListWidgetItem* changed_deck_item);

    /**
     * @brief  Open file dialog.
     */
    void response_open_file_push_button_clicked();

private:
    /**
     * A push-button for opening files.
     */
    QPushButton* open_file_push_button;

    /**
     * A widget for managing deck names.
     */
    QListWidget* deck_name_list_widget;

    /**
     * Handling files.
     */
    QFileDialog* file_dialog;

    /**
     * Flag denotes whether the user selects one deck item in front-end.
     */
    bool is_deck_name_chosen;
};
