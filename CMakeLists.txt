cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(avoid_wall)

find_package(gz-transport13 REQUIRED OPTIONAL_COMPONENTS log)

add_executable(lidar_node lidar_node.cpp)
target_link_libraries(lidar_node gz-transport13::core)