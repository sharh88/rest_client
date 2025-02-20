#ifndef REST_CLIENT_HPP
#define REST_CLIENT_HPP

#include <string>
#include <vector>

/**
 * @brief A class for making REST API requests.
 */
class RestClient {
public:
    /**
     * @brief Makes a GET request to the specified URL.
     * @param url The URL to make the GET request to.
     * @return The response from the server as a string, or an empty string if an error occurs.
     */
    std::string makeGetRequest(std::string& url);
    
private:
    
    /**
     * @brief Connects to a socket.
     * @param host The hostname to connect to.
     * @param port The port to connect to.
     * @return The socket file descriptor, or -1 if an error occurs.
     */
    int connectSocket(const std::string& host, int port);

    /**
     * @brief Closes a socket.
     * @param socket_fd The socket file descriptor to close.
     */
    void closeSocket(int socket_fd);

    /**
     * @brief Sends a GET request to the server.
     * @param endpoint The API endpoint.
     * @param host The hostname.
     * @param socket_fd The socket file descriptor.
     */
    void sendGetRequest(const std::string& endpoint, const std::string& host, int socket_fd);

    /**
     * @brief Receives the response from the server, check the response code, 
     * and return the response content.
     * @param socket_fd The socket file descriptor.
     * @return The response content from the server as a string.
     */
    std::string receiveResponse(int socket_fd);

    /**
     * @brief Gets the HTTP status code from the response.
     * @param response The HTTP response string.
     * @return The HTTP status code as an integer.
     */
    int getHttpStatusCode(const std::string& response);

    /**
     * @brief Parses a URL into its components (host, port, path).
     * @param[in] url The URL to parse.
     * @param[out] host The output parameter for the host.
     * @param[out] port The output parameter for the port.
     * @param[out] path The output parameter for the path.
     */
    void parseUrl(const std::string& url, std::string& host, int& port, std::string& path);
};

#endif // REST_CLIENT_HPP
