#include "Anker.hpp"

Anker::Anker(QObject* parent)
    : QObject(parent), deck_name_list_model(new QStringListModel())
{
    // For displaying deck names in hierarchy
    for(auto& deck_name : get_deck_names())
    {
        deck_name_list << QString::fromStdString(deck_name);
    }

    deck_name_list_model->setStringList(deck_name_list);

    QObject::connect(this, &Anker::deck_name_list_model_changed, this, &Anker::response_to_deck_name_list_model_changed);
    QObject::connect(this, &Anker::file_urls_changed, this, &Anker::response_to_file_urls_changed);
}

Anker::~Anker()
{
    delete deck_name_list_model;
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
    const std::string& front_content,
    const std::string& back_content,
    const std::vector< std::string >& tags,
    const std::string& note_type,
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
    // TODO: Trim file:/// of a Qt path
    foreach(QUrl file_url, new_file_urls)
    {
        if(file_url.fileName().toStdString().find(".mp3") != std::string::npos)
            files_mapper.insert( {trim_qt_file_url_prefix(file_url), ""} );
    }
    foreach(QUrl file_url, new_file_urls)
    {
        if(file_url.fileName().toStdString().find(".lrc") != std::string::npos)
        {
            // Form lrc file's corresponding mp3 file path
            std::string mp3_file_path = file_url.toString().toStdString().substr(0, (file_url.toString().toStdString().size()-3)) + "mp3";
            files_mapper[trim_qt_file_url_prefix(mp3_file_path)] = trim_qt_file_url_prefix(file_url);
        }
    }

    for(auto file_pair : files_mapper)
    {
        // 1. Move mp3 file to Anki media folder and change its name to the unique string;
        // 2. The reference of mp3 file in Anki is in the form of: [sound:ODH_encn_Collins_inextricable_0.mp3];
        // 3. Trim the leading text of *.lrc files;

        std::string unique_identifier = get_unique_identifier();

        move_file_to_anki_media_folder(file_pair.first.data(), unique_identifier + ".mp3");

        std::string anki_audio_link = "[sound:" + unique_identifier + ".mp3]";

        std::ifstream lrc_file(file_pair.second.data());
        if(!lrc_file.is_open())
        {
            // log it
            continue;
        }

        // lrc_string is in the form of: "[00:00.00]Silicon Valley is the cradle of innovation"
        std::ostringstream lrc_string_stream;
        lrc_string_stream << lrc_file.rdbuf();

        // Trim the leading "[00:00.00]"
        std::string lrc_string = lrc_string_stream.str().substr(10);

        // TODO: let user select deck
        add_note(
            "aboboo",
            anki_audio_link,
            lrc_string,
            {}
        );
    }
}

std::string Anker::get_unique_identifier()
{
    time_t now = std::time(0);
    tm* current_time = std::gmtime(&now);
    char current_time_string[30];
    std::strftime(current_time_string, 30, "%d-%b-%Y-%H-%M-%S-", current_time);

    auto generate_random_char = []()->char
    {
        const char char_set[] = "0123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(char_set) - 1);
        return char_set[ rand() % max_index ];
    };

    std::string random_string(10, 0);

    std::generate_n(random_string.begin(), 10, generate_random_char);

    return current_time_string + random_string;
}

bool Anker::move_file_to_anki_media_folder(const std::string& file_path, const std::string& new_file_name)
{
    // Open file
    std::ifstream input_file(file_path, std::ios::binary);
    if(!input_file.is_open())
        return false;

    // Transfer the file to Anki media folder
    // Anki media folder in my case: "C:\Users\16605\AppData\Roaming\Anki2\User 1\collection.media"
    std::string appdata_path = getenv("APPDATA");

    std::string anki_media_folder = appdata_path + "/Anki2/User 1/collection.media/";

    std::ofstream output_file((anki_media_folder + new_file_name), std::ios::binary);
    if(!output_file.is_open())
        return false;
    output_file << input_file.rdbuf();

    // Clear up
    input_file.close();
    output_file.close();
    return true;
}

std::string Anker::trim_qt_file_url_prefix(const QUrl& file_url_with_prefix)
{
    if(file_url_with_prefix.toString().toStdString().find("file:///") == std::string::npos)
        return file_url_with_prefix.toString().toStdString();
    return file_url_with_prefix.toString().toStdString().substr(8);
}

std::string Anker::trim_qt_file_url_prefix(const std::string& file_url_with_prefix)
{
    if(file_url_with_prefix.find("file:///") == std::string::npos)
        return file_url_with_prefix;
    return file_url_with_prefix.substr(8);
}

void Anker::set_deck_name_list_model(QStringListModel* new_deck_name_list_mode)
{
    deck_name_list_model = new_deck_name_list_mode;
    emit deck_name_list_model_changed(new_deck_name_list_mode);
}

QStringListModel* Anker::get_deck_name_list_model() const
{
    return deck_name_list_model;
}

void Anker::response_to_deck_name_list_model_changed(const QStringListModel* new_deck_name_list_mode)
{
    QStringList deck_name_list = new_deck_name_list_mode->stringList();
    foreach(auto& deck_name, deck_name_list)
    {
        qDebug() << "Deck Name: " << deck_name << '\n';
    }
}
