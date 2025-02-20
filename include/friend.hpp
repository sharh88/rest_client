#ifndef FRIEND_HPP
#define FRIEND_HPP

#include <string>
#include <vector>

class Friend {
private:
    std::string name;
    std::vector<std::string> hobbies;

public:
    Friend(const std::string& name, const std::vector<std::string>& hobbies):name(name), hobbies(hobbies) {}

    std::string getName() const { return name; }
    std::vector<std::string> getHobbies() const { return hobbies; }
};

#endif // FRIEND_HPP
