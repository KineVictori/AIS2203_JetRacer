
include(FetchContent)
set(SIMPLE_SOCKET_BUILD_TESTS OFF)
FetchContent_Declare(
        SimpleSocket
        GIT_REPOSITORY https://github.com/markaren/SimpleSocket.git
        GIT_TAG 96d28d34fed63a9888f52dad282227f40f0f1122
)
FetchContent_MakeAvailable(SimpleSocket)

set(SHARED_SOURCES
        Steering.cpp
)

add_library(Steering ${SHARED_SOURCES})
target_link_libraries(Steering PRIVATE simple_socket)
target_include_directories(Steering PUBLIC ${CMAKE_SOURCE_DIR}/include)