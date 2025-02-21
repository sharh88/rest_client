#include "json_parser.hpp"
#include <iostream>

std::unique_ptr<std::vector<User>> JSONParser::parse(std::string& json_data) {
    std::unique_ptr<std::vector<User>> users = std::make_unique<std::vector<User>>();

    size_t start = 0;
    int braceCount = 0; // To track the curly braces balance

    for (size_t i = 0; i < json_data.size(); ++i) {
        if (json_data[i] == '{') {
            if (braceCount == 0) {
                start = i;  // Mark the start of a new JSON object
            }
            braceCount++;  // Increment brace count when we encounter '{'
        } else if (json_data[i] == '}') {
            braceCount--;  // Decrement brace count when we encounter '}'
            if (braceCount == 0) {

                try {
                    // Parse the JSON data
                    nlohmann::json json_item = nlohmann::json::parse(json_data.substr(start, i- start + 1));
                    
                    // Create User object using the parsed JSON object
                    if (json_item.contains("id") && json_item.contains("name") &&
                        json_item.contains("city") && json_item.contains("age") && 
                        json_item.contains("friends") && json_item["friends"].is_array()) {

                        int id =  json_item["id"];
                        std::string name = json_item["name"];
                        std::string city = json_item["city"];
                        int age = json_item["age"];

                        std::vector<Friend> friends;
                        for (const auto& friendData : json_item["friends"]) {
                            friends.push_back(JSONParser::parseFriend(friendData));
                        }
                        
                        users->emplace_back(id, name, city, age, friends);
                    }
                    else{
                        std::cerr << "Warning: JSON data is missing some fields: skipping it." << std::endl;
                    }
                    
                } catch (const nlohmann::json::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }
    }

    return users;
}

Friend JSONParser::parseFriend(const nlohmann::json& friendData) {
    std::string name = friendData["name"];
    std::vector<std::string> hobbies;
    if (friendData.contains("hobbies") && friendData["hobbies"].is_array()) {
        for (const auto& hobby : friendData["hobbies"]) {
            hobbies.push_back(hobby);
        }
    }
    return Friend(name, hobbies);
}
