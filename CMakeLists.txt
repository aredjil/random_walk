cmake_minimum_required(VERSION 3.10)
project(main.x)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(main.x main.cpp)
target_link_libraries(main.x sfml-graphics sfml-window sfml-system)
