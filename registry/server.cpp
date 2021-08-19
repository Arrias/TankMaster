#include <vector>
#include "Room/Room.h"
#include "../mongoose/mongoose.h"
#include "../util/IpAddress/IpAddress.h"
#include "TcpGameHost/TcpGameHost.h"
#include <iostream>

using std::vector;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
vector<Room> rooms;
vector<shared_ptr<TcpGameHost>> games;

IpAddress address("http://localhost", "8080");
string text_type = "Content-Type: text/html; charset=utf-8\r\n";
string json_type = "Content-Type: application/json\r\n";

string getRoomsJson() {
    StringBuffer sb;
    PrettyWriter<rapidjson::StringBuffer> writer(sb);
    writer.StartArray();
    for (auto room : rooms) {
        room.serialize(writer);
    }
    writer.EndArray();
    return sb.GetString();
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
                mg_http_reply(c, 200, json_type.c_str(), getRoomsJson().c_str());
            }
        } else if (method == "POST") {
            if (mg_http_match_uri(hm, "/rooms/create")) {
                Room new_room;
                if (new_room.deserialize_from_json(body)) {
                    games.push_back(std::make_shared<TcpGameHost>(stoi(new_room.address.value.port)));
                    games.back()->launch();
                    rooms.push_back(new_room);
                    mg_http_reply(c, 201, text_type.c_str(), "Created");
                } else {
                    mg_http_reply(c, 400, text_type.c_str(), "Bad request");
                }
            } else if (mg_http_match_uri(hm, "/rooms/remove")) {
                Room new_room;

                bool incorrect_query = true;

                if (new_room.deserialize_from_json(body)) {
                    auto it_room = find(rooms.begin(), rooms.end(), new_room);
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