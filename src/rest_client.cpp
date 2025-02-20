#include "rest_client.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <regex>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

namespace {
    constexpr unsigned long BUFFER_SIZE = 5000;
}

void RestClient::close_socket(int socket_fd) {
    if (socket_fd != -1) {
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#else
        close(socket_fd);
#endif
    }
}

int RestClient::connect_socket(const std::string& host, int port) {
    struct addrinfo hints{}, *res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Resolve hostname to an IP address
    std::string port_str = std::to_string(port);
    if (getaddrinfo(host.c_str(), port_str.c_str(), &hints, &res) != 0) {
        throw std::runtime_error("Failed to resolve host: " + host);
    }

    // Create socket
    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        freeaddrinfo(res);
        throw std::runtime_error("Failed to create socket");
    }

    // Connect to the resolved address
    if (connect(sock, res->ai_addr, res->ai_addrlen) == -1) {
        freeaddrinfo(res);
#ifdef _WIN32
        closesocket(sock);
#else
        close(sock);
#endif
        throw std::runtime_error("Failed to connect to server");
    }

    freeaddrinfo(res);

    return sock;
}

void RestClient::send_request(const std::string& endpoint, const std::string& host, int socket_fd) {
    std::string request = "GET " + endpoint + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    send(socket_fd, request.c_str(), request.size(), 0);
}

std::string RestClient::receive_response(int socket_fd) {
    char buffer[BUFFER_SIZE] = {0};
    std::string response;
    int bytes_received;
    
    while ((bytes_received = recv(socket_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        response.append(buffer, bytes_received);
    }
    return response;
}

void RestClient::parse_url(const std::string& url, std::string& host, int& port, std::string& path) {
    // Example: http://test.brightsign.io:3000/path/to/resource
    std::regex url_regex(R"(^([^:]+)://([^:]+)(?::(\d+))?(.*)$)");
    std::smatch match;
    std::string port_str;

    if (std::regex_match(url, match, url_regex)) {
        std::string protocol = match[1];
        host = match[2];
        port_str = match[3];  // Will be empty if no port
        path = match[4]; // The rest of the url
    } else {
        std::cerr << "Invalid URL format" << std::endl;
    }

    if (!port_str.empty()) {
        port = std::stoi(port_str); // Convert to integer
    } else {
        port = -1;
    }

    if (path.empty()) {
        path = "/";
    }
}

// Function to extract the HTTP status code
int RestClient::get_http_status_code(const std::string& response) {
    std::istringstream stream(response);
    std::string http_version;
    int status_code;
    std::string status_message;

    // Read the first line: "HTTP/1.1 200 OK"
    if (stream >> http_version >> status_code) {
        return status_code;  // Return the extracted HTTP status code
    }

    return -1; // Error case
}

std::string RestClient::make_request(std::string &url) {
    std::string host;
    int port;
    std::string path;

    // Parse the full URL into host, port, and path
    parse_url(url, host, port, path);
    
    int sock = connect_socket(host, port);
    send_request(path, host, sock);
    std::string response = receive_response(sock);
    close_socket(sock);

    // Parse the HTTP status code and check if it's successful (200)
    int status_code = get_http_status_code(response);
    if (status_code != 200) {
        throw std::runtime_error("HTTP request failed with status code: " + std::to_string(status_code));
    }

    // Extract JSON data (skip headers)
    size_t json_start = response.find("{");
    if (json_start == std::string::npos) {
        throw std::runtime_error("Invalid HTTP response: Missing JSON data.");
    }

    return response.substr(json_start);  // Return JSON part of the response
}
