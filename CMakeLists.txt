cmake_minimum_required(VERSION 3.31)
project(AIS2203_JetRacer)

set(CMAKE_CXX_STANDARD 20)

set(OpenCV_DIR "C:/Program Files/opencv/build/x64/vc16/lib")
find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
