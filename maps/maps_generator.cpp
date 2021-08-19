#include "../rapidjson/rapidjson.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/filewritestream.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/document.h"
#include "../util/geometry/Vector/Vector.h"
#include "Map.h"

using rapidjson::FileWriteStream;

void write_map_to_file(FILE* file, Map map) {
    StringBuffer  sb;
    PrettyWriter<StringBuffer> pw(sb);
    map.serialize(pw);
    char buffer[1024];
    FileWriteStream fs(file, buffer, sizeof(buffer));
    PrettyWriter<FileWriteStream> writer(fs);
    Document document;
    document.Parse(sb.GetString());
    document.Accept(writer);
}

int main() {
    StringBuffer  sb;
    PrettyWriter<StringBuffer> pw(sb);
    Map map;
    //добавляем блоки на карту
    //...
    //добавляем блоки на карту
    FILE* file = fopen("../maps/map2.json", "wb");
    write_map_to_file(file, map);
    return 0;
}