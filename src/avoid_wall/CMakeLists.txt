cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(avoid_wall)

# Gazebo target
find_package(gz-transport13 REQUIRED)
find_package(gz-msgs10 REQUIRED)

add_executable(lidar_node_gz src/lidar_node_gz.cpp)
target_link_libraries(lidar_node_gz
    gz-transport13::core
    gz-msgs10::core
)

# ROS 2 target
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(lidar_node_ros src/lidar_node_ros.cpp)
ament_target_dependencies(lidar_node_ros
    rclcpp
    sensor_msgs
    geometry_msgs
)

install(TARGETS lidar_node_ros
    DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch/ DESTINATION share/${PROJECT_NAME}/launch)
install(DIRECTORY worlds/ DESTINATION share/${PROJECT_NAME}/worlds)

ament_package()