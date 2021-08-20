#pragma once

#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/document.h"
#include "../../util/InitializeValue/InitializeValue.h"

#include "string"

using rapidjson::PrettyWriter;
using rapidjson::StringBuffer;
using rapidjson::Document;

struct Address {
    std::string host, port;

    Address() {}

    Address(std::string host, std::string port) : host(host), port(port) {}

    bool operator==(const Address &oth) const {
        return host == oth.host && port == oth.port;
    }

    template<class T>
    bool deserialize_from_document(T &document) {
        InitializeValue<std::string> n_host;
        InitializeValue<std::string> n_port;
        for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it) {
            std::string key = it->name.GetString();

            if (!it->value.IsString()) continue;
            std::string value = it->value.GetString();

            if (key == "host") {
                n_host = value;
            } else if (key == "port") {
                n_port = value;
            }
        }
        bool success = n_host.wasInitialized && n_port.wasInitialized;
        if (success) {
            port = n_port.value;
            host = n_host.value;
        }
        return success;
    }

    bool deserialize_from_json(const std::string &json) {
        Document document;
        document.Parse(json.c_str());
        return deserialize_from_document(document);
    }

    void serialize(PrettyWriter<StringBuffer> &pw) const {
        pw.StartObject();
        pw.String("host");
        pw.String(host.c_str());
        pw.String("port");
        pw.String(port.c_str());
        pw.EndObject();
    }

    std::string getAddress() const {
        return host + ":" + port;
    }
};