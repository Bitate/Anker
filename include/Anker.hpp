#pragma once

#include "httplib.h"

#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <ctime>
#include <strstream>
#include <iostream>
#include <regex>

#include <json/json.h>

#include <QList>
#include <QUrl>
#include <QObject>
#include <QString>
#include <QApplication>
#include <QProgressDialog>
#include <QDebug>
#include <QStringListModel>

class Anker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString import_deck_name WRITE set_import_deck_name)
    Q_PROPERTY(QList<QUrl> file_urls READ get_file_urls WRITE set_file_urls NOTIFY file_urls_changed)
    Q_PROPERTY(QStringListModel* deck_name_list_model READ get_deck_name_list_model WRITE set_deck_name_list_model NOTIFY deck_name_list_model_changed)
    // Lifetime management
public:
    explicit Anker(QObject* parent = nullptr);
    ~Anker();

    // Normal public functions
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
    
    bool has_deck(const std::string& deck_name);

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

    
    bool get_last_record_from_clipboard();

    /**
     * @brief  Whether the response string contains error indicator.
     * @param  response  Response json object.
     * @return  True if the request failed.
     */
    bool is_request_failed(const Json::Value& response);

    std::string get_unique_identifier();

    bool move_file_to_anki_media_folder(const std::string& file_path, const std::string& new_file_name);
    
    /**
     * @brief  Trim the leading "file:///" of given file url.
     * @param  file_url_with_prefix  File url to be trimmed.
     * @return  Trimmed std::string.
     */
    std::string trim_qt_file_url_prefix(const QUrl& file_url_with_prefix);

    std::string trim_qt_file_url_prefix(const std::string& file_url_with_prefix);

    void pop_up_error_dialog(const std::string& error_title, const std::string& error_info);

    // Qt getters
public:
    QList<QUrl> get_file_urls() const;
    QStringListModel* get_deck_name_list_model() const;

    // Qt setters
public:
    void set_file_urls(const QList<QUrl>& new_file_urls);
    void set_deck_name_list_model(QStringListModel* new_deck_name_list_mode);
    void set_import_deck_name(const QString& new_import_deck_name);

    // Qt signals
signals:
    void file_urls_changed(const QList<QUrl>& new_file_urls);
    void deck_name_list_model_changed(const QStringListModel* new_deck_name_list_mode);

    // Qt slots
public slots:
    void response_to_file_urls_changed(const QList<QUrl>& new_file_urls);
    void response_to_deck_name_list_model_changed(const QStringListModel* new_deck_name_list_mode);

private:
    QList<QUrl> file_urls;
    std::map<std::string, std::string> files_mapper;

    QString import_deck_name;
    QStringList deck_name_list;
    QStringListModel* deck_name_list_model;

    QProgressDialog* import_progress_dialog;
};
