#include "Anker.hpp"

std::string Anker::send_request( Json::Value& request )
{
    httplib::Client client("localhost", 8765);

    Json::StreamWriterBuilder string_builder;

    const std::string json_request = Json::writeString(string_builder, request);

    auto response = client.Post("/", json_request, "application/json");

    if(response->status != 200)
    {
        return {};
    }

    return response->body;
}

std::string Anker::add_note( 
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

    return send_request( request );
}

std::vector< std::string > Anker::get_deck_names()
{
    Json::Value request;
    request["action"] = "deckNames";
    request["version"] = 6;


    Json::Value response_json( send_request( request ) );

    std::cout << response_json["result"];

    if( send_request( request ) == "\"error\": null" )
        return { {} };
    else // error happened
        return { {} };
}