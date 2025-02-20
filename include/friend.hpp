#ifndef FRIEND_HPP
#define FRIEND_HPP

#include <string>
#include <vector>

/**
 * @brief Represents a friend with their name and hobbies.
 */
class Friend {
private:
    std::string name; /// The name of the friend.
    std::vector<std::string> hobbies; /// A vector of the friend's hobbies.

public:
    /**
     * @brief Constructs a new Friend object.
     * @param name The name of the friend.
     * @param hobbies A vector of the friend's hobbies.
     */
    Friend(const std::string& name, const std::vector<std::string>& hobbies):name(name), hobbies(hobbies) {}

    /**
     * @brief Gets the name of the friend.
     * @return The name of the friend.
     */
    std::string getName() const { return name; }

    /**
     * @brief Gets the vector of the friend's hobbies.
     * @return A vector of the friend's hobbies.
     */
    std::vector<std::string> getHobbies() const { return hobbies; }
};

#endif // FRIEND_HPP
