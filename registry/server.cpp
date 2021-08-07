//
// Created by arrias on 08.08.2021.
//
#include <vector>
#include "Room/Room.h"
#include "../mongoose/mongoose.h"
#include <iostream>

using std::vector;

vector<Room> rooms;
string host = "localhost";
string port = "8080";

string getHttpAddress() {
    return "http://" + host + ":" + port;
}

string getRoomsJson() {
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
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

        if (method == "GET") {
            if (mg_http_match_uri(hm, "/health")) {
                mg_http_reply(c, 200, "", "OK");
            } else if (mg_http_match_uri(hm, "/rooms")) {
                mg_http_reply(c, 200, "", getRoomsJson().c_str());
            }
        } else if (method == "POST") {
            if (mg_http_match_uri(hm, "/rooms/create")) {
                rapidjson::Document document;
                document.Parse(hm->body.ptr);
                Room new_room;

                if (new_room.deserialize(document)) {
                    rooms.push_back(new_room);
                    mg_http_reply(c, 201, "", "Created");
                } else {
                    mg_http_reply(c, 400, "", "Bad request");
                }
            } else if (mg_http_match_uri(hm, "/rooms/remove")) {
                rapidjson::Document document;
                document.Parse(hm->body.ptr);
                Room new_room;

                bool incorrect_query = true;

                if (new_room.deserialize(document)) {
                    auto it_room = find(rooms.begin(), rooms.end(), new_room);
                    if (it_room != rooms.end()) {
                        rooms.erase(it_room);
                        incorrect_query = false;
                        mg_http_reply(c, 200, "", "OK");
                    }
                }

                if (incorrect_query) {
                    mg_http_reply(c, 400, "", "Bad request");
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, getHttpAddress().c_str(), fn, NULL);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}