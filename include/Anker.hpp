#pragma once

#include "httplib.h"
#include "MainWindow.hpp"

#include <map>
#include <regex>
#include <stack>
#include <ctime>
#include <string>
#include <fstream>
#include <strstream>

#include <json/json.h>

#include <QUrl>
#include <QList>
#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QApplication>
#include <QProgressDialog>

class Anker : public QObject
{
    Q_OBJECT

    // Lifetime management
public:
    explicit Anker(QObject* parent = nullptr);
    ~Anker();

public:     
    /**
     * @brief  Send json request to anki.
     * @param  request  Json request.
     * @return  Response Json object.
     */
    Json::Value send_request( Json::Value& request );
    
    /**
     * @brief  Create deck based on given deck_name.
     * @return  True if succeeds.
     * @remark  Deck name is in the form of 'math::calculus'
     *          Use '::' to represent the hierarchy of deck names.
     */
    bool create_deck(const std::string& deck_name);
    
    /**
     * @brief  Whether Anki has given deck with the name of @b deck_name.
     * @return  True if Anki has that deck.
     */
    bool has_deck(const std::string& deck_name);

    /**
     * @brief  Delete card with the name of @b card_name.
     * @return  True if succeeds.
     */
    bool delete_card(const std::string& card_name);

    /**
     * @brief  Deletes decks with the given names. 
     * @param  deck_name  Name of the deck to be deleted.
     * @param  cards_too  A flag denotes whether the cards will be deleted winthin that deck.
     * @remark  If cards_too is true (defaults to false if unspecified), 
     *          the cards within the deleted decks will also be deleted; 
     *          otherwise they will be moved to the default deck.
     */
    bool delete_deck(const std::string& deck_name, const bool cards_too = false);
    
    /**
     * @brief  Add a new note to anki.
     * @param  deck_name  Deck name.
     * @param  front_content  Front card's content.
     * @param  back_content  Back card's content.
     * @param  tags  An array of tags.
     * @param  note_type  Note type with default value of "basic"
     * @param  allow_duplicate  Is allowed to have duplicate note?
     * @return  True if succeeds.
     */
    bool add_note( 
        const std::string& deck_name,
        const std::string& front_content,
        const std::string& back_content,
        const std::vector< std::string >& tags,
        const std::string& note_type = "basic",
        const bool allow_duplicate = false
    );

    /**
     * @brief  Get a vector of deck names.
     * @return  An array of deck names.
     */
    std::vector< std::string > get_deck_names();

    /**
     * @brief  Get the content at the top of clipboard,
     *         namely the latest one.
     * @return  True if succeeds.
     */
    bool get_last_record_from_clipboard();

    /**
     * @brief  Whether the response string contains error indicator.
     * @param  response  Response json object.
     * @return  True if the request failed.
     */
    bool is_request_failed(const Json::Value& response);

    /**
     * @brief  Get unique string.
     * @return  Unique string.
     */
    std::string get_unique_identifier();

    /**
     * @brief  Move mp3 file to Anki media foler.
     * @param  file_path  Mp3 file path.
     * @param  new_file_name  Anki media folder path + mp3 file path.
     * @return  True if succeeds.
     */
    bool move_file_to_anki_media_folder(const std::string& file_path, const std::string& new_file_name);
    
    /**
     * @brief  Trim the leading "file:///" of given file url.
     * @param  file_url_with_prefix  File url to be trimmed.
     * @return  File string without "file:///" at the beginning.
     */
    std::string trim_qt_file_url_prefix(const QUrl& file_url_with_prefix);

    /**
     * @brief  Trim the leading "file:///" of given file url.
     * @param  file_url_with_prefix  File url string to be trimmed.
     * @return  File string without "file:///" at the beginning.
     */
    std::string trim_qt_file_url_prefix(const std::string& file_url_with_prefix);

    /**
     * @brief Display main window GUi.
     */
    void show_main_window();

    // Qt slots
public slots:
    /**
     * @brief  Handle file urls selected by user.
     * @param  new_file_urls  User selected file urls.
     * @remark  Move mp3 file to Anki media folder and change the name to the unique string;
     */
    void response_file_urls_changed(const QList<QUrl>& new_file_urls);

    /**
     * @brief  Handle deck item state changed(either selected or unselected by user).
     * @param changed_deck_item  Deck item.
     */
    void response_deck_item_state_changed(const QListWidgetItem* changed_deck_item);
    
private:
    /**
     * Stores user selected file urls.
     */
    QList<QUrl> file_urls;

    /**
     * mp3 file name as key, while lrc file name as value.
     */
    std::map<std::string, std::string> files_mapper;

    /**
     *  User selected deck name.
     */
    QString chosen_deck_name;

    /**
     * All deck names in a list.
     */
    QStringList deck_name_list;

    /**
     * Progress dialog object.
     */
    QProgressDialog* import_progress_dialog;

    /**
     * For managing main window GUI.
     */
    MainWindow main_window;
};
