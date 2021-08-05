//
// Created by arrias on 05.08.2021.
//
#include <string>
#include "../../rapidjson/prettywriter.h"

#pragma once

using std::string;
using namespace rapidjson;

struct User {
    int id;
    string name;

    void serialize(PrettyWriter<StringBuffer> &writer) {
        writer.StartObject();
        writer.String("id");
        writer.Uint(id);
        writer.String("name");
        writer.String(name.c_str(), static_cast<SizeType>(name.length()));
        writer.EndObject();
    }
};


