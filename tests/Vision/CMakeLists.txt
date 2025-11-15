
include(FetchContent)
set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/IslandRock1/SimpleSocket.git
        GIT_TAG "master"
)
FetchContent_MakeAvailable(SimpleSocket)

add_executable(testClient testClient.cpp)
target_link_libraries(testClient PUBLIC ${OpenCV_LIBRARIES} simple_socket visionClient)
