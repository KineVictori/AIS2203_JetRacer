
set(SHARED_SOURCES
        Steering.cpp
)

add_library(Steering ${SHARED_SOURCES})
target_include_directories(Steering PRIVATE ${CMAKE_SOURCE_DIR}/include/Steering)