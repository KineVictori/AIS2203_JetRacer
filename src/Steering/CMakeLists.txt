
include(FetchContent)
set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/IslandRock1/SimpleSocket.git
        GIT_TAG "master"
)
FetchContent_MakeAvailable(SimpleSocket)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

set(SHARED_SOURCES
        Steering.cpp
)

add_library(Steering ${SHARED_SOURCES})
target_link_libraries(Steering PUBLIC simple_socket nlohmann_json) # I want this to be private, but it does not work..?

target_include_directories(Steering PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(pybind11)
if(pybind11_FOUND)
    pybind11_add_module(SteeringPython pybind.cpp)
    target_link_libraries(SteeringPython PRIVATE Steering)
endif()