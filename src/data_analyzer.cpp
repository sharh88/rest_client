#include "data_analyzer.hpp"
#include <iostream>

DataAnalyzer::DataAnalyzer(const std::unique_ptr<std::vector<User>> users) {
    for (const auto& user : *users) {
        map_user_city[user.getCity()].push_back(user);
    }
}

nlohmann::json DataAnalyzer::getStatistics() const {
    nlohmann::json statistics;

    statistics["AVG Age Users per City"] = computeAverageAgePerCity();
    statistics["AVG Friends per City"] = computeAverageFriendsPerCity();
    statistics["User w/ most Friends per City"] = findUserWithMostFriendsPerCity();
    statistics["Common First Name"] = findMostCommonFirstName();
    statistics["Most Common Friend's Hobby"] = findMostCommonHobby();
    
    return statistics;
}

// Computes the average age of users per city
nlohmann::json DataAnalyzer::computeAverageAgePerCity() const {
    
    nlohmann::json avgAgePerCity;
    
    for (const auto& [city, users] : map_user_city) {
        if (!users.empty()) {
            double totalAge = std::accumulate(users.begin(), users.end(), 0.0,
                [](double sum, const User& user) { return sum + user.getAge(); });
            avgAgePerCity[city] = totalAge / users.size();
        } else {
            avgAgePerCity[city] = 0.0;
        }
    }
    return avgAgePerCity;
}

// Computes the average number of friends per user in each city
nlohmann::json  DataAnalyzer::computeAverageFriendsPerCity() const {
    
    nlohmann::json avgFriendsPerCity;
    
    for (const auto& [city, users] : map_user_city) {
        if (!users.empty()) {
            double totalFriends = std::accumulate(users.begin(), users.end(), 0.0,
                [](double sum, const User& user) { return sum + user.getFriends().size(); });
            avgFriendsPerCity[city] = totalFriends / users.size();
        } else {
            avgFriendsPerCity[city] = 0.0;
        }
    }
    return avgFriendsPerCity;
}

// Finds the user with the most friends per city
nlohmann::json  DataAnalyzer::findUserWithMostFriendsPerCity() const {
    
    nlohmann::json mostFriendsPerCity;
    
    for (const auto& [city, users] : map_user_city) {
        if (!users.empty()) {
            auto maxUser = std::max_element(users.begin(), users.end(),
                [](const User& a, const User& b) { return a.getFriends().size() < b.getFriends().size(); });
            mostFriendsPerCity[city] = {{"name", maxUser->getName()}, 
                                        {"friend_count", maxUser->getFriends().size()}};
        }
    }
    return mostFriendsPerCity;
}

// Finds the most common first name across all cities
std::string DataAnalyzer::findMostCommonFirstName() const {
    
    std::unordered_map<std::string, int> firstNameCount;
    
    for (const auto& [city, users] : map_user_city) {
        for (const auto& user : users) {
            firstNameCount[user.getName()]++;
        }
    }

    auto mostCommon = std::max_element(firstNameCount.begin(), firstNameCount.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    return (mostCommon != firstNameCount.end()) ? mostCommon->first : "";
}

// Finds the most common hobby among all friends in all cities
std::string DataAnalyzer::findMostCommonHobby() const {
    
    std::unordered_map<std::string, int> hobbyCount;
    
    for (const auto& [city, users] : map_user_city) {
        for (const auto& user : users) {
            for (const auto& friendObj : user.getFriends()) {
                for (const auto& hobby : friendObj.getHobbies()) {
                    hobbyCount[hobby]++;
                }
            }
        }
    }

    auto mostCommon = std::max_element(hobbyCount.begin(), hobbyCount.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    return (mostCommon != hobbyCount.end()) ? mostCommon->first : "";
}
