
include(FetchContent)
set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/IslandRock1/SimpleSocket.git
        GIT_TAG "master"
)
FetchContent_MakeAvailable(SimpleSocket)

set(SHARED_SOURCES
        visionClient.cpp
)

add_library(visionClient ${SHARED_SOURCES})
target_link_libraries(visionClient PUBLIC ${OpenCV_LIBRARIES} simple_socket)
target_include_directories(visionClient PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 QUIET)
if(pybind11_FOUND)
    pybind11_add_module(VisionPython pybind.cpp)
    target_link_libraries(VisionPython PRIVATE visionClient)
endif()
