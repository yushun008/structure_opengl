cmake_minimum_required(VERSION 3.26)

project(structured_opengl)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/opencv/4.8.1_2")
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3")
include_directories("/opt/homebrew/Cellar/glfw/3.3.8/include")
link_directories("/opt/homebrew/Cellar/glfw/3.3.8/lib")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
