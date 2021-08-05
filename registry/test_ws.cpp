//
// Created by arrias on 05.08.2021.
//

#include "../mongoose/mongoose.h"

static const char *s_url = "ws://localhost:8000/websocket";

// Print websocket response and signal that we're done
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_ERROR) {
        // On error, log error message
        LOG(LL_ERROR, ("%p %s", c->fd, (char *) ev_data));
    } else if (ev == MG_EV_WS_OPEN) {
        // When websocket handshake is successful, send message
        mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {
        // When we get echo response, print it
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        printf("GOT ECHO REPLY: [%.*s]\n", (int) wm->data.len, wm->data.ptr);
    }

    if (ev == MG_EV_ERROR || ev == MG_EV_CLOSE || ev == MG_EV_WS_MSG) {
        *(bool *) fn_data = true;  // Signal that we're done
    }
}

int main(void) {
    struct mg_mgr mgr;        // Event manager
    bool done = false;        // Event handler flips it to true
    struct mg_connection *c;  // Client connection
    mg_mgr_init(&mgr);        // Initialise event manager
    c = mg_ws_connect(&mgr, s_url, fn, &done, NULL);     // Create client
    while (c && done == false) { mg_mgr_poll(&mgr, 1000); }  // Wait for echo
    mg_mgr_free(&mgr);                                   // Deallocate resources
    return 0;
}