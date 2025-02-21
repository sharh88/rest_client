#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <vector>
#include <memory>
#include "user.hpp"
#include <nlohmann/json.hpp>

/**
 * @brief A utility class for parsing JSON data into User and Friend objects.
 *
 * This class provides static methods for parsing JSON strings and nlohmann::json objects.
 * It is designed to be a utility class and cannot be instantiated.
 */
class JSONParser {
public:
    // Delete constructor and destructor to prevent instantiation
    JSONParser() = delete;
    ~JSONParser() = delete;

    // Delete copy/move constructors as well
    JSONParser(const JSONParser&) = delete;
    JSONParser& operator=(const JSONParser&) = delete;
    
    /**
     * @brief Parses a JSON string into a vector of User objects.
     * @param json_data The JSON string to parse.
     * @return A unique pointer to a vector of User objects.
     */
    static std::unique_ptr<std::vector<User>> parse(std::string& json_data);

    /**
     * @brief Parses a nlohmann::json object into a Friend object.
     * @param friendData The nlohmann::json object representing friend data.
     * @return A Friend object.
     */
    static Friend parseFriend(const nlohmann::json& friendData);
};

#endif // JSON_PARSER_HPP
