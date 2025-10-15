
set(SHARED_SOURCES
        ../../tests/vision/testVision.cpp
)

add_library(testLib ${SHARED_SOURCES})
target_link_libraries(testLib PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(testLib PRIVATE ${CMAKE_SOURCE_DIR}/include/vision)