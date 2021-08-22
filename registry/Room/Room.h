#pragma once
#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/document.h"
#include "../../util/Address/Address.h"
#include "../../util/InitializeValue/InitializeValue.h"
#include <random>
#include <chrono>
#include <iostream>

using std::string;

struct Room {
    InitializeValue<string> creator_name;
    InitializeValue<int> places_cnt;
    InitializeValue<int> free_places;
    InitializeValue<Address> address;

    struct Identifier : public string {
        void serialize(PrettyWriter<StringBuffer> &pw) const {
            pw.StartObject();
            pw.String("id");
            pw.String(this->c_str());
            pw.EndObject();
        }

        template<class T>
        bool deserialize_from_document(T &document) {
            if(!document.IsObject())
                return false;
            if (document.HasMember("id")) {
                if (document["id"].IsString()) {
                    *((string*)(this)) = document["id"].GetString();
                    return true;
                } else return false;
            } else return false;
        }

        bool deserialize_from_json(const std::string &json) {
            rapidjson::Document document;
            document.Parse(json.c_str());
            return deserialize_from_document(document);
        }
    };

    static Identifier generate_identifier(const int len = 6) {
        Room::Identifier identifier;
        std::mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());
        for (int i = 0; i < len; i++)
            identifier.push_back('a' + rnd() % 26);
        return identifier;
    }

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
        if(!document.IsObject()) return false;

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
        return creator_name.wasInitialized && places_cnt.wasInitialized && free_places.wasInitialized &&
               address.wasInitialized;
    }

    bool operator==(const Room &other) {
        return creator_name == other.creator_name && places_cnt == other.places_cnt &&
               free_places == other.free_places &&
               address == other.address;
    }
};


