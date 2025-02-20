#ifndef USER_HPP
#define USER_HPP

#include "friend.hpp"

#include <string>
#include <vector>

class User {
private:
    int id;
    std::string name;
    std::string city;
    int age;
    std::vector<Friend> friends;

public:
    User(int id, const std::string& name, const std::string& city, int age, const std::vector<Friend>& friends)
        : id(id), name(name), city(city), age(age), friends(friends) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCity() const { return city; }
    int getAge() const { return age; }
    std::vector<Friend> getFriends() const { return friends; }
};

#endif // USER_HPP
