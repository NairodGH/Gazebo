// only for the tutorial, real world application uses ROS2 directly (Gazebo is just a simulator) so check lidar_node_ros.cpp instead

#include <gz/msgs/laserscan.pb.h>
#include <gz/msgs/twist.pb.h>
#include <gz/transport/Node.hh>

gz::transport::Node* g_node = nullptr;
gz::transport::Node::Publisher g_pub;

void cb(const gz::msgs::LaserScan& _msg)
{
    gz::msgs::Twist data;
    bool clear = true;

    for (int i = 0; i < _msg.ranges_size(); i++) {
        if (_msg.ranges(i) < 1.0) {
            clear = false;
            break;
        }
    }
    data.mutable_linear()->set_x(clear ? 0.5 : 0.0);
    data.mutable_angular()->set_z(clear ? 0.0 : 0.5);
    g_pub.Publish(data);
}

int main(int argc, char** argv)
{
    gz::transport::Node node;
    g_node = &node;
    g_pub = node.Advertise<gz::msgs::Twist>("/cmd_vel");

    if (!node.Subscribe("/lidar", cb)) {
        std::cerr << "Error subscribing to /lidar" << std::endl;
        return -1;
    }
    gz::transport::waitForShutdown();
    return 0;
}