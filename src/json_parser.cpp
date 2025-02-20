#include "json_parser.hpp"
#include <iostream>

std::unique_ptr<std::vector<User>> JSONParser::parse(const std::string& json_data) {
    std::unique_ptr<std::vector<User>> users = std::make_unique<std::vector<User>>();

    // Split the input string by newlines into separate JSON objects
    std::istringstream stream(json_data);
    std::string line;

     // Read and parse each JSON object
    while (std::getline(stream, line)) {
        try {
            // Parse the JSON data
            nlohmann::json json_item = nlohmann::json::parse(line);
            
            // Create User object using the parsed JSON object
            int id = json_item["id"];
            std::string name = json_item["name"];
            std::string city = json_item["city"];
            int age = json_item["age"];

            std::vector<Friend> friends;
            if (json_item.contains("friends") && json_item["friends"].is_array()) {
                for (const auto& friendData : json_item["friends"]) {
                    friends.push_back(JSONParser::parseFriend(friendData));
                }
            }
            users->emplace_back(id, name, city, age, friends);
            
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
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
