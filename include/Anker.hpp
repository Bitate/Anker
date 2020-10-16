#pragma once

#include "Card.hpp"
#include "httplib.h"

#include <string>
#include <json/json.h>

class Anker
{
public:     
    /**
     * @brief  Send json request to anki.
     * @param  request  Json request.
     * @return  Response Json string from Anki.
     */
    std::string send_request( Json::Value& request );
    
    /**
     * @brief  Add a new note to anki.
     * @param  deck_name  Deck name.
     * @param  note_type  Note type.
     * @param  front_content  Front card's content.
     * @param  back_content  Back card's content.
     * @param  tags  An array of tags.
     * @param  allow_duplicate  Is allowed to have duplicate note?
     * @return  Response Json string from Anki.
     */
    std::string add_note( 
        const std::string& deck_name,
        const std::string& note_type,
        const std::string& front_content,
        const std::string& back_content,
        const std::vector< std::string >& tags,
        const bool allow_duplicate = false
    );
};