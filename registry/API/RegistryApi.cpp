//
// Created by arrias on 09.08.2021.
//

#include "RegistryApi.h"
#include <iostream>

RegistryApi::RegistryApi(IpAddress registry_ip) : registry_ip(registry_ip) {
    if (registry_ip.port.empty()) {
        http.setHost(registry_ip.host);
    } else {
        http.setHost(registry_ip.host, stoi(registry_ip.port));
    }
}

std::vector<Room> deserialize(std::string json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    std::vector<Room> ret;

    for (auto &v : document.GetArray()) {
        Room room;
        if (room.deserialize_from_document(v)) {
            ret.push_back(room);
        }
    }

    return ret;
}

std::vector<Room> RegistryApi::get_rooms() {
    sf::Http::Request request("/rooms", sf::Http::Request::Get);
    auto response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        rooms = deserialize(response.getBody());
    }
    return rooms;
}
