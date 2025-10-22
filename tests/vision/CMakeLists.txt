add_executable(test testVision.cpp)
target_link_libraries(test PUBLIC ${OpenCV_LIBRARIES} visionLib)

find_package(Threads REQUIRED)
target_link_libraries(test PRIVATE Threads::Threads)
