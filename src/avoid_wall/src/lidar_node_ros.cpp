#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

// ROS2 version of lidar_node_gz using ros_gz
class WallAvoider : public rclcpp::Node {
public:
    WallAvoider()
        : Node("wall_avoider")
    {
        pub_ = create_publisher<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10); // how many incoming messages to buffer if your callback is slower than the publish rate
        sub_ = create_subscription<sensor_msgs::msg::LaserScan>("/lidar",
            10, // how many outgoing messages to buffer if the downstream subscriber is slower than you publish
            std::bind(&WallAvoider::cb, this, std::placeholders::_1));
    }

private:
    void cb(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        bool clear = true;
        for (float range : msg->ranges) {
            if (range < 1.0f) {
                clear = false;
                break;
            }
        }
        geometry_msgs::msg::Twist twist;
        twist.linear.x = clear ? 0.5 : 0.0;
        twist.angular.z = clear ? 0.0 : 0.5;
        pub_->publish(twist);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WallAvoider>());
    rclcpp::shutdown();
    return 0;
}