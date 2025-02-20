#ifndef DATAANALYZER_HPP
#define DATAANALYZER_HPP
#include "user.hpp"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <vector>

class DataAnalyzer {
private:
    std::unordered_map<std::string, std::vector<User>> map_user_city;

public:
    DataAnalyzer() = delete;
    explicit DataAnalyzer(const std::unique_ptr<std::vector<User>> users);
    nlohmann::json calculateAverageAge();
    nlohmann::json calculateAverageFriends();
    nlohmann::json findUserWithMostFriends();
    std::string findMostCommonFirstName();
    std::string findMostCommonHobby();
};
#endif // DATAANALYZER_HPP
