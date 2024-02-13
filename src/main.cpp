#include <iostream>

#include "mongocxx/instance.hpp"

#include "mongodb_handler.hh"
#include <regex>
void addField(bsoncxx::builder::stream::document& doc, std::string key, std::string value);

int main() {
    bool result = 0;
    mongocxx::instance instance;
    learning::MongoDbHandler mongoDbHandler("mongodb://10.41.74.77:27017", "learning_mongocxx", "string2json"); //TODO move this to the constructor later
    bsoncxx::builder::stream::document doc;
    addField(doc, "sys.exec.out.time", "0.65");
    addField(doc, "sys.exec.out.time.cannon.pos[0]", "98");
    addField(doc, "sys.exec.out.time.cannon.pos[1]", "34");
    

    // Print the BSON document
    bsoncxx::document::value mydoc = doc << bsoncxx::builder::stream::finalize;
    
    std::cout << "----------------------------------------------------------------------"<< std::endl;
    std::cout << bsoncxx::to_json(mydoc.view()) << std::endl;

    // result = mongoDbHandler.add(doc);

    std::cout << "Hello from Fenix! operation is " << result << std::endl;
}

void addField(bsoncxx::builder::stream::document& doc, std::string key, std::string value) {
    // Check if key contains dot notation
    size_t dotPos = key.find('.');
    size_t bracketPos = key.find('[');

    if (dotPos != std::string::npos) {
        // Handle nested fields
        std::string nestedKey = key.substr(0, dotPos);
        bsoncxx::builder::stream::document nestedDoc;
        addField(nestedDoc, key.substr(dotPos + 1), value); //recursive call
        doc << nestedKey << nestedDoc;
    } else if (bracketPos != std::string::npos) {
        // Handle array fields
        std::string arrayKey = key.substr(0, bracketPos);
        int arrayIndex = std::stoi(key.substr(bracketPos + 1, key.length() - bracketPos - 2));
        doc << arrayKey << bsoncxx::builder::stream::open_array << value << bsoncxx::builder::stream::close_array;
    } else {
        // Add simple field
        doc << key << value;
    }
    std::cout << bsoncxx::to_json(doc) << std::endl;
}