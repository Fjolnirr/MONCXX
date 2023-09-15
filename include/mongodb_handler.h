#pragma once

#include <cstdint>
#include <string>

// "/usr/local/include/bsoncxx/v_noabi" include this to  include path
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/uri.hpp"

#include "character_size.h"

namespace learning
{

    constexpr char mongoDbUri[] = "mongodb:0.0.0.0:27017";
    constexpr char databaseName[] = "learning_mongocxx";
    constexpr char collectionName[] = "MarioKartCharacters";

    class MongoDbHandler
    {
    public:
        MongoDbHandler()
            : uri(mongocxx::uri(mongoDbUri)),
              client(mongocxx::client(uri)),
              db(client[databaseName]) {}

        bool AddCharacterToDb(const std::string &character_name,
                              const CharacterSize &size, const int16_t &wins)
        {
            mongocxx::collection collection = db[collectionName];
            auto builder = bsoncxx::builder::stream::document{};

            bsoncxx::document::value doc_to_add =
                builder << "characterName" << character_name
                        << "size" << character_size_to_string.find(size)->second
                        << "wins" << wins << bsoncxx::builder::stream::finalize;

            collection.insert_one(doc_to_add.view());

            return true;
        }

        bool UpdateWins(const std::string &character_id)
        {
            return true;
        }

        bool RemoveCharacterFromDb(const std::string &character_id)
        {
            return true;
        }

    private:
        mongocxx::uri uri;
        mongocxx::client client;
        mongocxx::database db;
    };
}