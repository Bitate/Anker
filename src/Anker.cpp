#include "Anker.hpp"

Anker::Anker(QObject* parent)
    : QObject(parent)
{
    QObject::connect(this, &Anker::file_urls_changed, this, &Anker::response_to_file_urls_changed);
}

Json::Value Anker::send_request( Json::Value& request )
{
    httplib::Client client("localhost", 8765);

    Json::StreamWriterBuilder string_builder;

    const std::string json_request = Json::writeString(string_builder, request);

    auto response = client.Post("/", json_request, "application/json");

    if(response->status != 200)
    {
        return Json::objectValue;
    }

    /**
     * How to convert std::string to Json::Value?
     * https://stackoverflow.com/a/50084636/11850070
     */
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    Json::Value json;
    std::string errors;

    bool parsing_succeeds = reader->parse(
        response->body.c_str(),
        response->body.c_str() + response->body.size(),
        &json,
        &errors
    );

    delete reader;

    if(!parsing_succeeds)
    {
        return Json::objectValue;
    }

    return json;
}

bool Anker::add_note( 
    const std::string& deck_name,
    const std::string& note_type,
    const std::string& front_content,
    const std::string& back_content,
    const std::vector< std::string >& tags,
    const bool allow_duplicate
)
{
    /**
     * For add note sample jason request
     * https://github.com/FooSoft/anki-connect/blob/master/actions/notes.md#note-actions
     */
    Json::Value note_fields;
    note_fields["Front"] = front_content;
    note_fields["Back"] = back_content;

    Json::Value note_tags(Json::arrayValue);
    for(int i = 0; i < tags.size(); ++i)
        note_tags[i] = tags[i];
    
    Json::Value note_options;
    note_options["allowDuplicate"] = allow_duplicate;

    Json::Value params_note;
    params_note["deckName"] = deck_name;
    params_note["modelName"] = note_type;
    params_note["fields"] = note_fields;
    params_note["tags"] = note_tags;
    params_note["options"] = note_options;

    Json::Value request_params;
    request_params["note"] = params_note;

    Json::Value request;
    request["action"] = "addNote";
    request["version"] = 6;
    request["params"] = request_params;

    return !is_request_failed( send_request(request) );
}

std::vector< std::string > Anker::get_deck_names()
{
    // Sample request:

    // {
    //     "action": "deckNames",
    //     "version": 6
    // }

    Json::Value request;
    request["action"] = "deckNames";
    request["version"] = 6;

    Json::Value result_array = send_request(request)["result"];

    std::vector< std::string > deck_names;
    for(auto& deck_name : result_array)
    {
        deck_names.push_back(deck_name.asString());
    }
    
    return deck_names;
}

bool Anker::create_deck(const std::string& deck_name)
{   
    // Sample request:

    // {
    //     "action": "createDeck",
    //     "version": 6,
    //     "params": {
    //         "deck": "Japanese::Tokyo"
    //     }
    // }
    
    Json::Value request_params;
    request_params["deck"] = deck_name;

    Json::Value request;
    request["action"] = "createDeck";
    request["version"] = 6;
    request["params"] = request_params;

    return !is_request_failed( send_request(request) );
}

bool Anker::has_deck(const std::string& deck_name)
{
    std::vector< std::string > deck_names = get_deck_names();

    for(auto& anki_deck_name : deck_names)
        if(anki_deck_name == deck_name)
            return true;

    return false;
}

bool Anker::is_request_failed(const Json::Value& response)
{
    return response.toStyledString().find("\"error\" : null") == std::string::npos ? true : false;
}

bool Anker::delete_deck(const std::string& deck_name, const bool cards_too)
{
    // Sample request:

    // {
    //     "action": "deleteDecks",
    //     "version": 6,
    //     "params": 
    //     {
    //         "decks": ["Japanese::JLPT N5", "Easy Spanish"],
    //         "cardsToo": true
    //     }
    // }

    Json::Value deck_names(Json::arrayValue);
    deck_names[0] = deck_name;
    
    Json::Value request_params;
    request_params["decks"] = deck_names;
    request_params["cardsToo"] = cards_too;

    Json::Value request;
    request["action"] = "deleteDecks";
    request["version"] = 6;
    request["params"] = request_params;

    return !is_request_failed( send_request(request) );
}

void Anker::set_file_urls(const QList<QUrl>& new_file_urls)
{
    file_urls = new_file_urls;
    emit file_urls_changed(new_file_urls);
}

QList<QUrl> Anker::get_file_urls() const
{
    return file_urls;
}

void Anker::response_to_file_urls_changed(const QList<QUrl>& new_file_urls)
{
    // Map each mp3 file to a corresponding lrc file.
    foreach(QUrl file_url, new_file_urls)
    {
        if(file_url.fileName().toStdString().find(".mp3") != std::string::npos)
            files_mapper.insert( {file_url.toString().toStdString(), ""} );
    }
    foreach(QUrl file_url, new_file_urls)
    {
        if(file_url.fileName().toStdString().find(".lrc") != std::string::npos)
        {
            // Form lrc file's corresponding mp3 file path
            std::string mp3_file_path = file_url.toString().toStdString().substr(0, (file_url.toString().toStdString().size()-3)) + "mp3";
            files_mapper[mp3_file_path] = file_url.toString().toStdString();
        }
    }

    for(auto file_pair : files_mapper)
    {
        // e.g. First is:  file:///D:/Torrent Download/Aboboooooo/201210225151/9.mp3
        qDebug() << "First is: " << file_pair.first.data() << '\n';
        // e.g. Second is:  file:///D:/Torrent Download/Aboboooooo/201210225151/9.lrc
        qDebug() << "Second is: " << file_pair.second.data() << '\n';
    }
}


