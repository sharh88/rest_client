# Json Rest Library

## Description

This project is a simple REST client. It fetches JSON data from an API endpoint, processes it, and computes statistics on user information.


## JSON Object Structure

The application expects a JSON response with the following structure:

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