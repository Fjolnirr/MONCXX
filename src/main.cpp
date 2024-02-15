#include <iostream>
#include <nlohmann/json.hpp>
#include <mongocxx/instance.hpp>

#include "mongodb_handler.hh"
#include <regex>

using json = nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

bsoncxx::builder::basic::document jsonIterator(const json& j, const std::string& parentKey );
void string2json(json &j, std::string str, std::string value);

int main() {
    bool result = 0;
    mongocxx::instance instance;
    learning::MongoDbHandler mongoDbHandler("mongodb://10.41.74.77:27017", "learning_mongocxx", "string2json"); //TODO move this to the constructor later
    // basic::document builds a BSON document.
    json j;
    string2json(j, "sys.exec.out.time", "0.65"); 
    string2json(j, "sys.exec.out.dyn.cannon.pos[0]", "98"); 
    string2json(j, "sys.exec.out.dyn.cannon.pos[1]", "34");
    string2json(j, "sys.exec.out.dyn.cannon.vel[1][1].dim", "1");
    string2json(j, "sys.exec.out.dyn.cannon.vel[0][0]", "1");
    std::cout << "from json: " << j.dump() << std::endl;
    std::cout << "\n*********************************************************" << std::endl;

    // auto doc = bsoncxx::builder::basic::document{};
    // doc = jsonIterator(j, "");

    // serialize it to BSON
    std::vector<std::uint8_t> v = json::to_bson(j);
    // create a bsoncxx::document::view from the data
    auto d = bsoncxx::document::view(v.data(), v.size());
    std::cout << "\n----------------------------------------------------------------------"<< std::endl;
    std::cout << "from bson: " << bsoncxx::to_json(d) << std::endl;

    result = mongoDbHandler.add(d);

    std::cout << "Hello from Fjolnirr! operation is " << result << std::endl;
}

/*
IF PARAM IS OBJ -> MAKE DOCUMENT
IF PARAM IS ARR -> MAKE ARRAY
ELSE KVP
*/
bsoncxx::builder::basic::document jsonIterator(const json& j, const std::string& parentKey = "") {
    auto doc = bsoncxx::builder::basic::document{};
    auto arr = bsoncxx::builder::basic::array{};
    if (j.is_object()) {
        for (json::const_iterator it = j.begin(); it != j.end(); ++it) {
            // std::string key = parentKey.empty() ? it.key() : parentKey + "." + it.key();
            std::string key = it.key();
            std::cout << key << " : ";

            if (it.value().is_object() || it.value().is_array()) {
                std::cout << "\n";
                std::string currKey = it.key();

                auto sub_doc = jsonIterator(it.value(), key);
                if(!it.value().is_array()){
                    doc.append(kvp(currKey, sub_doc));
                }
            } else {
                std::cout << it.value() << "\n";
                std::string key = it.key();
                std::string value = it.value();
                doc.append(kvp(key, value));
            }
        }
    } else if (j.is_array()) {
        std::string key = parentKey;
        for (size_t i = 0; i < j.size(); ++i) {
            // std::string key = parentKey + "[" + std::to_string(i) + "]";
            // std::string key = parentKey;
            std::cout << key << " : ";

            if (j[i].is_object() || j[i].is_array()) {
                std::cout << "\n";
                auto sub_doc = jsonIterator(j[i], "");
                arr.append(sub_doc);
            } else {
                std::cout << j[i] << "\n";
                std::string value = j[i];
                arr.append(value);
            }
        }
        doc.append(kvp(key, arr));
    }
    return doc;
}

void string2json(json &j, std::string str, std::string value) {
    replace(str.begin(), str.end(), '.', '/');
    replace(str.begin(), str.end(), '[', '/');
    str.erase(remove(str.begin(), str.end(), ']'), str.end());

    j[json::json_pointer('/' + str)] = value;
    std::cout << j.dump() << "\n";
}
