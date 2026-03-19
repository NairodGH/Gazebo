import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, TimerAction

def generate_launch_description():
    world = os.path.join(get_package_share_directory('avoid_wall'), 'worlds', 'building_robot.sdf')

    return LaunchDescription([
        ExecuteProcess(
            cmd=['gz', 'sim', world],
        ),
        TimerAction(period=3.0, actions=[
            Node(
                package='ros_gz_bridge',
                executable='parameter_bridge',
                arguments=[
                    '/lidar@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan',
                    '/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist',
                    '/imu@sensor_msgs/msg/Imu[gz.msgs.IMU',
                ],
                output='screen',
            ),
            Node(
                package='avoid_wall',
                executable='lidar_node_ros',
                output='screen',
            ),
        ]),
    ])