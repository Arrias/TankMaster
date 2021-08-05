//
// Created by arrias on 05.08.2021.
//
#include "../mongoose/mongoose.h"
#include <string>
#include <iostream>
#include <vector>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/prettywriter.h"
#include "../web/User/User.h"
#include <thread>
#include "SFML/Graphics.hpp"
#include <algorithm>

using namespace rapidjson;
using namespace std;
using namespace sf;

vector<User> users;

string getUsersObject() {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    writer.StartArray();
    for (auto i : users) {
        i.serialize(writer);
    }
    writer.EndArray();
    return sb.GetString();
}

static const char *s_listen_on = "http://localhost:8000";
static const char *s_web_directory = ".";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        if (strcmp(hm->method.ptr, "POST")) {
            if (mg_http_match_uri(hm, "/rooms")) {
                printf("%s\n", hm->body.ptr);
                Document d;
                d.Parse(hm->body.ptr);
                int id = stoi(d["id"].GetString());
                string name = d["name"].GetString();
                User new_user = {id, name};
                users.push_back(new_user);
            }
        }

        if (mg_http_match_uri(hm, "/websocket")) {
            // Upgrade to websocket. From now on, a connection is a full-duplex
            // Websocket connection, which will receive MG_EV_WS_MSG events.
            mg_ws_upgrade(c, hm, NULL);
        } else if (mg_http_match_uri(hm, "/rest")) {
            // Serve REST response
            mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
        } else {
            // Serve static files
            struct mg_http_serve_opts opts = {.root_dir = s_web_directory};
            mg_http_serve_dir(c, (mg_http_message *) ev_data, &opts);
        }
    } else if (ev == MG_EV_WS_MSG) {
        // Got websocket frame. Received data is wm->data. Echo it back!
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
        mg_iobuf_delete(&c->recv, c->recv.len);
    } else if (ev == MG_EV_WS_OPEN) {
        struct mg_http_message *wm = (struct mg_http_message *) ev_data;
        cout << "SAU" << endl;
    } else if (ev == MG_EV_CLOSE) {
        cout << "DOSVIDOS" << endl;
    }
    (void) fn_data;
}

void UI() {
    RenderWindow window(VideoMode(500, 500), "Registry");
    window.setFramerateLimit(50);

    Font font;
    font.loadFromFile("../fonts/ArialBlack/ArialBlack.ttf");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
            auto als = getUsersObject();
            Text text;
            text.setFillColor(sf::Color::Red);
            text.setString(getUsersObject());
            text.setFont(font);
            text.setCharacterSize(24);

            window.clear(Color(0, 0, 0));
            window.draw(text);
            window.display();
        }
    }
}

int main(int argc, char *argv[]) {
     thread thr(UI);

    struct mg_mgr mgr;                            // Event manager
    mg_mgr_init(&mgr);                            // Initialise event manager
    mg_http_listen(&mgr, s_listen_on, fn, NULL);  // Create HTTP listener
    for (;;) mg_mgr_poll(&mgr, 1000);             // Infinite event loop
    mg_mgr_free(&mgr);
    return 0;
}