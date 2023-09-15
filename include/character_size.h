#pragma once

#include <ostream>

#include <unordered_map>

namespace learning
{
    enum class CharacterSize
    {
        Small,
        Medium,
        Large
    };

    // map size enums to string(or char*)
    std::unordered_map<CharacterSize, const std::string> character_size_to_string({{CharacterSize::Small, "small"},
                                                                              {CharacterSize::Medium, "medium"},
                                                                              {CharacterSize::Large, "large"}});
}