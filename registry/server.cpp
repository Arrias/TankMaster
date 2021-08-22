#include <vector>
#include "Room/Room.h"
#include "../mongoose/mongoose.h"
#include "../util/Address/Address.h"
#include <iostream>
#include <random>
#include <chrono>

using std::vector;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
vector<std::pair<Room::Identifier, Room>> rooms;

Address address("http://localhost", "8081");
string text_type = "Content-Type: text/html; charset=utf-8\r\n";
string json_type = "Content-Type: application/json\r\n";

string get_identifier_json(const Room::Identifier &identifier) {
    StringBuffer sb;
    PrettyWriter<rapidjson::StringBuffer> writer(sb);
    identifier.serialize(writer);
    return sb.GetString();
}

string get_rooms_json() {
    StringBuffer sb;
    PrettyWriter<rapidjson::StringBuffer> writer(sb);
    writer.StartArray();
    for (const auto &room : rooms) {
        room.second.serialize(writer);
    }
    writer.EndArray();
    return sb.GetString();
}

vector<std::pair<Room::Identifier, Room>>::iterator find_room(Room::Identifier id) {
    auto it_room = find_if(rooms.begin(), rooms.end(),
                           [&id](const std::pair<Room::Identifier, Room> &room) {
                               return (room.first == id);
                           });
    return it_room;
}


static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        mg_http_message *hm = (mg_http_message *) ev_data;

        string method(hm->method.ptr, hm->method.ptr + hm->method.len);
        string body(hm->body.ptr, hm->body.ptr + hm->body.len);

        if (method == "GET") {
            if (mg_http_match_uri(hm, "/health")) {
                mg_http_reply(c, 200, text_type.c_str(), "OK");
            } else if (mg_http_match_uri(hm, "/rooms")) {
                mg_http_reply(c, 200, json_type.c_str(), get_rooms_json().c_str());
            }
        } else if (method == "POST") {
            if (mg_http_match_uri(hm, "/rooms")) {
                Room room;
                if (room.deserialize_from_json(body)) {
                    const Room::Identifier id = Room::generate_identifier();
                    rooms.emplace_back(id, room);
                    mg_http_reply(c, 201, json_type.c_str(), get_identifier_json(id).c_str());
                } else {
                    mg_http_reply(c, 400, text_type.c_str(), "Bad request");
                }
            }
        } else if (method == "PUT") {
            if (mg_http_match_uri(hm, "/rooms")) {
                Room room;
                Room::Identifier id;

                bool incorrect_query = true;
                Document document;
                document.Parse(body.c_str());

                if (document.HasMember("id") && id.deserialize_from_document(document["id"])) {
                    if (document.HasMember("room") && room.deserialize_from_document(document["room"])) {
                        auto it_room = find_room(id);
                        if (it_room != rooms.end()) {
                            it_room->second = room;
                            incorrect_query = false;
                            mg_http_reply(c, 200, text_type.c_str(), "OK");
                        }
                    }
                    if (incorrect_query) {
                        mg_http_reply(c, 400, text_type.c_str(), "Bad request");
                    }
                }
            }
        } else if (method == "DELETE") {
            if (mg_http_match_uri(hm, "/rooms")) {
                Room::Identifier id;
                bool incorrect_query = true;
                if (id.deserialize_from_json(body)) {
                    auto it_room = find_room(id);
                    if (it_room != rooms.end()) {
                        rooms.erase(it_room);
                        incorrect_query = false;
                        mg_http_reply(c, 200, text_type.c_str(), "OK");
                    }
                }
                if (incorrect_query) {
                    mg_http_reply(c, 400, text_type.c_str(), "Bad request");
                }
            }
        }
        c->is_draining |= true;
    }
}

int main(int argc, char *argv[]) {
    mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, address.getAddress().c_str(), fn, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}