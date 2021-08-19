#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include "../../InitializeValue/InitializeValue.h"
#include "../../../rapidjson/rapidjson.h"
#include "../../../rapidjson/prettywriter.h"
#include "../../../rapidjson/stringbuffer.h"
#include "../../../rapidjson/document.h"

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
using rapidjson::Document;
using rapidjson::Value;

struct Vector {
    float x, y;

    float len();

    Vector(float x = 0, float y = 0);

    Vector(sf::Vector2f vec);

    sf::Vector2f to_sfml_vector() const;

    float scalar_prod(Vector oth);

    float vec_prod(Vector oth);

    Vector normalize();

    float polar();

    float angle_angle_between(Vector oth);

    Vector rotate(float angle);

    bool operator==(Vector oth);

    Vector operator+(Vector oth);

    Vector operator*(float scalar);

    Vector operator-(Vector oth);

    void operator+=(Vector oth);

    void operator-=(Vector oth);

    void operator*=(float scalar);

    friend sf::Packet& operator>> (sf::Packet &packet, Vector &v);
    friend sf::Packet& operator<< (sf::Packet &packet, Vector &v);

    template<class T>
    bool deserialize_from_document(T &document) {
        if(!document.IsObject()) return false;

        InitializeValue<float> n_x, n_y;
        if(document.HasMember("x"))
            if(document["x"].IsFloat())
                n_x = document["x"].GetFloat();
        if(document.HasMember("y"))
            if(document["y"].IsFloat())
                n_y = document["y"].GetFloat();

        bool success = n_x.wasInitialized && n_y.wasInitialized;
        if(success) {
            x = n_x.value;
            y = n_y.value;
        }
        return success;
    }

    bool deserialize_from_json(const std::string &json);

    void serialize(PrettyWriter<StringBuffer> &pw) const;
};

