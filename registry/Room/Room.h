#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/document.h"
#include "../../util/Address/Address.h"
#include "../../util/InitializeValue/InitializeValue.h"

#pragma once

using std::string;

struct Room {
    InitializeValue<string> creator_name;
    InitializeValue<int> places_cnt;
    InitializeValue<int> free_places;
    InitializeValue<Address> address;

    void serialize(PrettyWriter<StringBuffer> &pw) const {
        pw.StartObject();
        pw.String("creator_name");
        pw.String(creator_name.value.c_str());
        pw.String("places_cnt");
        pw.Int(places_cnt.value);
        pw.String("free_places");
        pw.Int(free_places.value);
        pw.String("address");
        address.value.serialize(pw);
        pw.EndObject();
    }
    template<class T>
    bool deserialize_from_document(T &document) {
        for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it) {
            string key = it->name.GetString();
            if (key == "creator_name") {
                if (it->value.IsString()) {
                    creator_name = it->value.GetString();
                }
            } else if (key == "places_cnt") {
                if (it->value.IsInt()) {
                    places_cnt = it->value.GetInt();
                }
            } else if (key == "free_places") {
                if (it->value.IsInt()) {
                    free_places = it->value.GetInt();
                }
            } else if (key == "address") {
                if (it->value.IsObject()) {
                    address.wasInitialized |= address.value.deserialize_from_document(it->value);
                }
            }
        }
        return valid();
    }

    bool deserialize_from_json(const std::string &json) {
        rapidjson::Document document;
        document.Parse(json.c_str());
        return deserialize_from_document(document);
    }

    bool valid() const {
        return creator_name.wasInitialized && places_cnt.wasInitialized && free_places.wasInitialized && address.wasInitialized;
    }

    bool operator==(const Room &other) {
        return creator_name == other.creator_name && places_cnt == other.places_cnt && free_places == other.free_places &&
               address == other.address;
    }
};


