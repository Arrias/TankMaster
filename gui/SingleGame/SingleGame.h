//
// Created by arrias on 31.07.2021.
//

#pragma once

#include "../Window/Window.h"
#include "../constants.h"
#include "../../rapidjson/rapidjson.h"
#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/stringbuffer.h"
#include "../../rapidjson/document.h"
#include "../../rapidjson/filereadstream.h"

using rapidjson::FileReadStream;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
using rapidjson::Document;
using rapidjson::Value;

struct SingleGame : public Window {
    SingleGame(Window base);

    void show() override;
};


