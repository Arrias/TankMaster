#include "Map.h"

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
using rapidjson::Document;

void Map::add_block(shared_ptr<Block> a) {
    if(a->get_id() == blocks.size())
        blocks.push_back(a);
}

const vector<shared_ptr<Block>>& Map::get_blocks() const {
    return blocks;
}

void Map::add_spawn_point(Vector point) {
    spawn_points.push_back(point);
}

vector<Vector> Map::get_spawn_points() const {
    return spawn_points;
}

bool Map::deserialize_from_json(const std::string &json) {
    Document document;
    document.Parse(json.c_str());
    return deserialize_from_document(document);
}

void Map::serialize(PrettyWriter <StringBuffer> &pw) const {
    pw.StartObject();
    pw.Key("blocks");
    pw.StartArray();
    for(auto &i : blocks)
        i->serialize(pw);
    pw.EndArray();
    pw.Key("spawn_points");
    pw.StartArray();
    for(auto &i : spawn_points)
        i.serialize(pw);
    pw.EndArray();
    pw.EndObject();
}

int Map::get_new_id() const {
    return blocks.size();
}

