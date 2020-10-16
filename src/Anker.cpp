#include "Anker.hpp"

std::string Anker::send_request( Json::Value& request )
{
    httplib::Client client("localhost", 8765);

    Json::StreamWriterBuilder string_builder;

    const std::string json_request = Json::writeString(string_builder, request);

    auto result = client.Post("/", json_request, "application/json");

    if(result->status != 200)
    {
        return {};
    }

    return result->body;
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

    send_request( request );

    return send_request( request );
}