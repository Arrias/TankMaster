//
// Created by arrias on 08.08.2021.
//
#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/document.h"
#include <string>

#pragma once

using std::string;
using rapidjson::PrettyWriter;
using rapidjson::StringBuffer;

template<class T>
struct InitializeValue {
    T value;
    int wasInitialized = false;

    InitializeValue &operator=(T new_value) {
        value = new_value;
        wasInitialized = true;
        return *this;
    }

    bool operator==(const InitializeValue<T> &oth) {
        return oth.value == value;
    }
};

struct Room {
    InitializeValue<string> creator_name;
    InitializeValue<int> places_cnt;
    InitializeValue<int> free_places;
    InitializeValue<string> address;

    void serialize(PrettyWriter<StringBuffer> &pw);

    bool deserialize(rapidjson::Document& document);

    bool valid() const;

    bool operator==(const Room &other);
};


