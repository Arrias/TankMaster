#include "RegistryApi.h"
#include <iostream>

RegistryApi::RegistryApi(Address registry_ip) : registry_ip(registry_ip) {
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

bool RegistryApi::create_room(const Room &room, Room::Identifier &id) {
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    room.serialize(writer);
    sf::Http::Request request("/rooms", sf::Http::Request::Post);
    request.setBody(sb.GetString());
    auto response = http.sendRequest(request);
    id.deserialize_from_json(response.getBody());
    return (response.getStatus() == sf::Http::Response::Created);
}

bool RegistryApi::edit_room(const Room &room, const Room::Identifier &id) {
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    writer.StartObject();
    writer.Key("id");
    id.serialize(writer);
    writer.Key("room");
    room.serialize(writer);
    writer.EndObject();

    sf::Http::Request request("/rooms", sf::Http::Request::Put);
    request.setBody(sb.GetString());
    auto response = http.sendRequest(request);

    return (response.getStatus() == sf::Http::Response::Ok);
}

std::vector<Room> RegistryApi::get_rooms() {
    sf::Http::Request request("/rooms", sf::Http::Request::Get);
    auto response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        rooms = deserialize(response.getBody());
    }
    return rooms;
}
