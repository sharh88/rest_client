#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <vector>
#include <memory>
#include "user.hpp"
#include <nlohmann/json.hpp>

class JSONParser {
public:
    // Delete constructor and destructor to prevent instantiation
    JSONParser() = delete;
    ~JSONParser() = delete;

    // Delete copy/move constructors as well
    JSONParser(const JSONParser&) = delete;
    JSONParser& operator=(const JSONParser&) = delete;
    
    static std::unique_ptr<std::vector<User>> parse(const std::string& json_data);
    static Friend parseFriend(const nlohmann::json& friendData);
};

#endif // JSON_PARSER_HPP
