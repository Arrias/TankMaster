//
// Created by arrias on 08.08.2021.
//

#include "Room.h"

void Room::serialize(PrettyWriter<StringBuffer> &pw) {
    pw.StartObject();
    pw.String("creator_name");
    pw.String(creator_name.value.c_str());
    pw.String("places_cnt");
    pw.Int(places_cnt.value);
    pw.String("free_places");
    pw.Int(free_places.value);
    pw.String("address");
    pw.String(address.value.c_str());
    pw.EndObject();
}

bool Room::valid() const {
    return creator_name.wasInitialized && places_cnt.wasInitialized && free_places.wasInitialized && address.wasInitialized;
}

bool Room::deserialize(rapidjson::Document &document) {
    for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it) {
        string key = it->name.GetString();
        string val = it->value.GetString();
        if (key == "creator_name") {
            creator_name = val;
        } else if (key == "places_cnt") {
            places_cnt = stoi(val);
        } else if (key == "free_places") {
            free_places = stoi(val);
        } else if (key == "address") {
            address = val;
        }
    }
    return valid();
}

bool Room::operator==(const Room &other) {
    return creator_name == other.creator_name && places_cnt == other.places_cnt && free_places == other.free_places &&
           address == other.address;
}


