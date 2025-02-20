#include <iostream>
#include <rest_client.hpp>
#include <json_parser.hpp>
#include <data_analyzer.hpp>
#include <user.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./rest_client <URL>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    RestClient client = RestClient();
    string response = client.make_request(url);
    unique_ptr<vector<User>> users = JSONParser::parse(response);
    DataAnalyzer analyzer(std::move(users));
    cout << analyzer.calculateAverageAge() << endl;
    cout << analyzer.calculateAverageFriends() << endl;
    cout << analyzer.findMostCommonFirstName() << endl;
    cout << analyzer.findMostCommonHobby() << endl;
    cout << analyzer.findUserWithMostFriends() << endl;
}