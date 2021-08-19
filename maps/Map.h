#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "../util/geometry/Vector/Vector.h"
#include "../engine/entities/Block/Block.h"
#include "../util/InitializeValue/InitializeValue.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/document.h"

using rapidjson::FileReadStream;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;
using rapidjson::Document;
using rapidjson::Value;
using std::shared_ptr;
using std::vector;

class Map {
public:
    int get_new_id() const;

    void add_block(shared_ptr<Block> a);
    const vector<shared_ptr<Block>>& get_blocks() const;
    void add_spawn_point(Vector point);
    vector<Vector> get_spawn_points() const;

    void loadFromFile(std::string path) {
        FILE* file = fopen(path.c_str(), "rb");
        char readBuffer[256];
        FileReadStream bis(file, readBuffer, sizeof(readBuffer));
        Document document;
        document.ParseStream(bis);
        deserialize_from_document(document);
        fclose(file);
    }

    template<class T>
    bool deserialize_from_document(T &document) {
        if(!document.IsObject()) return false;

        std::vector<std::shared_ptr<Block>> n_blocks;
        std::vector<Vector> n_spawn_points;

        if(document.HasMember("blocks")) {
            if(document["blocks"].IsArray()) {
                for (auto &it : document["blocks"].GetArray()) {
                    if(!it.IsObject()) continue;
                    Block block;
                    if(block.deserialize_from_document(it))
                        n_blocks.push_back(std::make_shared<Block>(block));
                }
            } else return false;
        } else return false;

        if(document.HasMember("spawn_points")) {
            if(document["spawn_points"].IsArray()) {
                for (auto &it : document["spawn_points"].GetArray()) {
                    if(!it.IsObject()) continue;
                    Vector vector;
                    if(vector.deserialize_from_document(it))
                        n_spawn_points.push_back(vector);
                }
            } else return false;
        } else return false;

        blocks = n_blocks;
        spawn_points = n_spawn_points;
        return true;
    }

    bool deserialize_from_json(const std::string &json);

    void serialize(PrettyWriter<StringBuffer> &pw) const;

private:
    vector<shared_ptr<Block>> blocks;
    vector<Vector> spawn_points;
};