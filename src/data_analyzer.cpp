#include "data_analyzer.hpp"
#include <iostream>

DataAnalyzer::DataAnalyzer(const std::unique_ptr<std::vector<User>> users) {
    for (const auto& user : *users) {
        map_user_city[user.getCity()].push_back(user);
    }
}

nlohmann::json DataAnalyzer::calculateAverageAge() {
    nlohmann::json result;
    for (const auto& [city, users] : map_user_city) {
        double totalAge = 0;
        for (const auto& user : users) {
            totalAge += user.getAge();
        }
        double averageAge = users.empty() ? 0 : totalAge / users.size();
        result[city] = averageAge;
    }
    return result;
}

nlohmann::json DataAnalyzer::calculateAverageFriends() {
    nlohmann::json result;
    for (const auto& [city, users] : map_user_city) {
        double totalFriends = 0;
        for (const auto& user : users) {
            totalFriends += user.getFriends().size();
        }
        double averageFriends = users.empty() ? 0 : totalFriends / users.size();
        result[city] = averageFriends;
    }
    return result;
}

nlohmann::json DataAnalyzer::findUserWithMostFriends() {
    nlohmann::json result;
    for (const auto& [city, users] : map_user_city) {
        std::string maxFriendUser = "";
        int maxFriends = -1;
        for (const auto& user : users) {
            std::vector<Friend> friends = user.getFriends();
            if (static_cast<int>(friends.size()) > maxFriends) {
                maxFriends = friends.size();
                maxFriendUser = user.getName();
            }
        }
        if (maxFriends != -1) {
            result[city] = {{"name", maxFriendUser}, {"friend_count", maxFriends}};
        }
    }
    return result;
}

std::string DataAnalyzer::findMostCommonFirstName() {
    std::map<std::string, int> nameCounts;
    for (const auto& [city, users] : map_user_city) {
        for (const auto& user : users) {
            std::string name = user.getName();
            std::string firstName = name.substr(0, name.find(' '));
            nameCounts[firstName]++;
        }
    }

    std::string mostCommonName;
    int maxCount = 0;
    for (const auto& [name, count] : nameCounts) {
        if (count > maxCount) {
            mostCommonName = name;
            maxCount = count;
        }
    }
    return mostCommonName;
}

std::string DataAnalyzer::findMostCommonHobby() {
    std::map<std::string, int> hobbyCounts;
    for (const auto& [city, users] : map_user_city) {
        for (const auto& user : users) {
            for (const auto& friend_obj : user.getFriends()) {
                for (const auto& hobby : friend_obj.getHobbies()) {
                    hobbyCounts[hobby]++;
                }
            }
        }
    }

    std::string mostCommonHobby;
    int maxCount = 0;
    for (const auto& [hobby, count] : hobbyCounts) {
        if (count > maxCount) {
            mostCommonHobby = hobby;
            maxCount = count;
        }
    }
    return mostCommonHobby;
}

