#include <gz/msgs/laserscan.pb.h>
#include <gz/msgs/twist.pb.h>
#include <gz/transport/Node.hh>

// declare the topic and the node that'll publish to it
gz::transport::Node node;
auto pub = node.Advertise<gz::msgs::Twist>("/cmd_vel");

// handle lidar message (go forward if no obstacle, turn if there is) then publish to twist topic
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
    pub.Publish(data);
}

// subscribe to lidar topic by registering a callback then waitForShutdown
int main(int argc, char** argv)
{
    if (!node.Subscribe("/lidar", cb)) {
        std::cerr << "Error subscribing to /lidar" << std::endl;
        return -1;
    }
    gz::transport::waitForShutdown();
    return 0;
}