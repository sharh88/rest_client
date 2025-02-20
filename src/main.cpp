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
    try {
        string response = client.makeGetRequest(url);
        unique_ptr<vector<User>> users = JSONParser::parse(response);
        DataAnalyzer analyzer(std::move(users));
        cout << analyzer.getStatistics() << endl;
    }
    catch (const std::runtime_error& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}