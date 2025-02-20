#ifndef USER_HPP
#define USER_HPP

#include "friend.hpp"

#include <string>
#include <vector>

/**
 * @brief Represents a user with their information and friends.
 */
class User {
private:
    int id;                     /// The unique ID of the user.
    std::string name;           /// The name of the user.
    std::string city;           /// The city where the user lives.
    int age;                    /// The age of the user.
    std::vector<Friend> friends;/// A vector of the user's friends.

public:
    /**
     * @brief Constructs a new User object.
     * @param id The unique ID of the user.
     * @param name The name of the user.
     * @param city The city where the user lives.
     * @param age The age of the user.
     * @param friends A vector of the user's friends.
     */
    User(int id, const std::string& name, const std::string& city, int age, const std::vector<Friend>& friends)
        : id(id), name(name), city(city), age(age), friends(friends) {}

    /**
     * @brief Gets the ID of the user.
     * @return The ID of the user.
     */
    int getId() const { return id; }

    /**
     * @brief Gets the name of the user.
     * @return The name of the user.
     */
    std::string getName() const { return name; }

    /**
     * @brief Gets the city where the user lives.
     * @return The city where the user lives.
     */
    std::string getCity() const { return city; }

    /**
     * @brief Gets the age of the user.
     * @return The age of the user.
     */
    int getAge() const { return age; }

    /**
     * @brief Gets the vector of the user's friends.
     * @return A vector of the user's friends.
     */
    std::vector<Friend> getFriends() const { return friends; }
};

#endif // USER_HPP
