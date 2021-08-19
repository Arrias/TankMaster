#pragma once
#include <set>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "../../../util/geometry/Vector/Vector.h"
#include "../../../util/geometry/Segment/Segment.h"
#include "../../../rapidjson/rapidjson.h"
#include "../../../rapidjson/prettywriter.h"
#include "../../../rapidjson/stringbuffer.h"
#include "../../../rapidjson/document.h"

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
using rapidjson::Document;
using rapidjson::Value;

class Block {
protected:
    Vector cords; // (!) coordinates of the center
    Vector size; // (width, height)
    int id;
    float angle;
public:
    Block(Vector cords = Vector(), Vector size = Vector(), int id = 0, float angle = 0);

    virtual void rotate(float add_angle);

    float get_angle() const;

    Vector get_size() const;

    Vector get_cords() const;

    int get_id() const;

    friend std::vector<Vector> get_block_points(Block *a);

    friend Intersection get_blocks_intersection(Block *a, Block *b);

    friend std::vector<Segment> get_bad_segments(Block *a, Block *b);

    friend sf::Packet& operator>> (sf::Packet &packet, Block &block);
    friend sf::Packet& operator<< (sf::Packet &packet, Block &block);


    template<class T>
    bool deserialize_from_document(T &document) {
        if(!document.IsObject()) return false;
        Vector n_cords, n_size;
        int n_id;
        float n_angle;

        if(document.HasMember("cords")) {
            if(!n_cords.deserialize_from_document(document["cords"]))
                return false;
        } else return false;
        if(document.HasMember("size")) {
            if(!n_size.deserialize_from_document(document["size"]))
                return false;
        } else return false;
        if(document.HasMember("id")) {
            if(document["id"].IsInt())
                n_id = document["id"].GetInt();
            else return false;
        } else return false;

        if(document.HasMember("angle")) {
            if(document["angle"].IsFloat())
                n_angle = document["angle"].GetFloat();
            else return false;

        } else return false;

        cords = n_cords;
        size = n_size;
        id = n_id;
        angle = n_angle;
        return true;
    }

    bool deserialize_from_json(const std::string &json);

    void serialize(PrettyWriter<StringBuffer> &pw) const;
};

bool point_in_block(Vector point, Block *block);

std::vector<Vector> get_block_points(Block *a);

Intersection get_blocks_intersection(Block *a, Block *b);

std::vector<Segment> get_bad_segments(Block *a, Block *b);