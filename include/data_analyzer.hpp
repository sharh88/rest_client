#ifndef DATAANALYZER_HPP
#define DATAANALYZER_HPP
#include "user.hpp"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <vector>

/**
 * @brief Analyzes user data and generates statistics.
 */
class DataAnalyzer {
private:
    /**
     * @brief A map of cities to vectors of users living in that city.
     */
    std::unordered_map<std::string, std::vector<User>> map_user_city;

public:
    /**
     * @brief Deleted default constructor.  DataAnalyzer must be initialized with user data.
     */
    DataAnalyzer() = delete;

    /**
     * @brief Constructs a DataAnalyzer object from a vector of users.
     * @param users A unique pointer to a vector of User objects.  The DataAnalyzer takes ownership of this pointer.
     */
    explicit DataAnalyzer(const std::unique_ptr<std::vector<User>> users);

    /**
     * @brief Gets overall statistics about the user data.
     * @return A nlohmann::json object containing the statistics.
     */
    nlohmann::json getStatistics() const;

    /**
     * @brief Computes the average age of users per city.
     * @return A nlohmann::json object containing the average age per city.
     */
    nlohmann::json computeAverageAgePerCity() const;

    /**
     * @brief Computes the average number of friends per city.
     * @return A nlohmann::json object containing the average number of friends per city.
     */
    nlohmann::json computeAverageFriendsPerCity() const;

    /**
     * @brief Finds the user with the most friends in each city.
     * @return A nlohmann::json object containing the user with the most friends per city.
     */
    nlohmann::json findUserWithMostFriendsPerCity() const;

    /**
     * @brief Finds the most common first name among all users.
     * @return The most common first name as a string.
     */
    std::string findMostCommonFirstName() const;

    /**
     * @brief Finds the most common hobby among all users.
     * @return The most common hobby as a string.
     */
    std::string findMostCommonHobby() const;
};
#endif // DATAANALYZER_HPP
