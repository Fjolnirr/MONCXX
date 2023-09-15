#include <iostream>

#include "mongocxx/instance.hpp"

#include "mongodb_handler.h"
#include "character_size.h"

int main() {

    mongocxx::instance instance;
    learning::MongoDbHandler mongoDbHandler;

    mongoDbHandler.AddCharacterToDb("Donkey Kong", learning::CharacterSize::Large, 0);

    std::cout << "Hello from Fenix!" << std::endl;
}