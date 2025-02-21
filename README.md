# JSON Rest Client Application

## Description

This project is a simple REST client. It fetches JSON data from an API endpoint, processes it, and computes statistics on user information.

## Features

- Fetch user data from a REST API using POSIX sockets
- Process users and categorize them by city
- Analyze user data to compute statistical insights
- Cross-platform support (Windows & Linux)


## JSON Data Structure

The application expects a JSON data response with the following structure:

```
[
    {
        "id": 1,
        "name": "Alice",
        "city": "New York",
        "age": 30,
        "friends": [
            {
                "name": "Bob",
                "hobbies": ["Reading", "Swimming"]
            },
            {
                "name": "Charlie",
                "hobbies": ["Gaming", "Running"]
            }
        ]
    }
    ...
    {
        "id": 100,
        "name": "Mark",
        "city": "Los Angeles",
        "age": 22,
        "friends": [
            {
                "name": "Olivia",
                "hobbies": ["Housework", "Playing Cards"]
            }
        ]
    }
]
```

## Requirements

- C++17 or later
- CMake 3.10 or later
- `nlohmann_json` library (automatically fetched via CMake)
- A POSIX-compatible network stack (for Linux/macOS)
- Winsock2 (for Windows)

## Installation

### 1. Clone the Repository

```
git clone https://github.com/sharh88/rest_client.git
cd rest_client
```

### 2. Build the Project

```
mkdir build && cd build
cmake ..
cmake --build .
```

### 3. Run the Application

```
./rest_client http://test.brightsign.io:3000
```

## Security Enhancements

### 1. Using HTTPS
To improve security, the application shall support HTTPS via OpenSSL, ensuring data is transmitted securely.

### 2. TLS 1.3 Secure Sockets
The use of TLS 1.3 will enable encrypted communication, ensuring data confidentiality and preventing interception.

### 3. Certificate Verification
The application shall verify the server certificates to prevent Man-in-the-Middle (MITM) attacks.

### 4. Input Validation & Sanitization
User input from JSON queries shall be validated to prevent injection attacks.

