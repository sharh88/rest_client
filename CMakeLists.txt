cmake_minimum_required(VERSION 3.10)
project(JsonRestLibrary)

set(CMAKE_CXX_STANDARD 17)

# FetchContent for nlohmann_json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

# Explicitly disable the tests (CMake option for testing)
set(BUILD_TESTING OFF CACHE BOOL "Disable testing" FORCE)

FetchContent_MakeAvailable(nlohmann_json)

# Include directories
include_directories(include)

# Add source files
add_executable(JsonRestLibrary
    src/json_parser.cpp
    src/rest_client.cpp
    src/main.cpp
)

# Link libraries
target_link_libraries(JsonRestLibrary nlohmann_json::nlohmann_json)