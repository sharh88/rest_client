#ifndef REST_CLIENT_HPP
#define REST_CLIENT_HPP

#include <string>
#include <vector>
#include "user.hpp"
#include "json_parser.hpp"

class RestClient {
public:
   std::string make_request(std::string& url);
    
private:
    
    int connect_socket(const std::string& host, int port);
    void close_socket(int socket_fd);
    void send_request(const std::string& endpoint, const std::string& host, int socket_fd);
    std::string receive_response(int socket_fd);
    int get_http_status_code(const std::string& response) ;
    void parse_url(const std::string& url, std::string& host, int& port, std::string& path);
};

#endif // REST_CLIENT_HPP
