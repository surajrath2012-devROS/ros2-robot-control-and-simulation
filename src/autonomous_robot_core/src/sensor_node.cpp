#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class SensorNode : public rclcpp::Node
{
public:
    SensorNode() : Node("sensor_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("raw_sensor_data", 10);
        timer_ = this->create_wall_timer
        (
            std::chrono::milliseconds(500),
            std::bind(&SensorNode::publish_distance, this)
        );
    }

private:
    void publish_distance()
    {
        auto message = std_msgs::msg::Int32();
        message.data = 42;

        RCLCPP_INFO(this->get_logger(), "Sensor is sending data: %d", message.data);
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorNode>());
    rclcpp::shutdown();

    return 0;
}