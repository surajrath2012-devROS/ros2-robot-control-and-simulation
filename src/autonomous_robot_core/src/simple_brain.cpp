#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <numeric>
#include "std_msgs/msg/int32.hpp"

class SimpleBrain : public rclcpp::Node
{
public:

    SimpleBrain() : Node("robot_brain_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "raw_sensor_data", 10,
            std::bind(&SimpleBrain::on_data_received, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Production Brain: Online and Listening");    
       
    }

private:
    void on_data_received(const std_msgs::msg::Int32::SharedPtr msg)
    {
        // [3] Deep STL Usage: Vector Management
        readings_.push_back(msg->data); // Add new data to the end

        // If we have more than 5 items, remove the oldest one (the front)
        if (readings_.size() > 5) {
            readings_.erase(readings_.begin());
        }
        // The STL Vector container
        // [4] Calculate a Moving Average (Production Data Filtering)
        double sum = std::accumulate(readings_.begin(), readings_.end(), 0.0);
        double average = sum / readings_.size();

        RCLCPP_INFO(this->get_logger(), "Data: %d | Avg of last 5: %.2f", msg->data, average);
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    std::vector<int> readings_; // The STL Vector container
    
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimpleBrain>());
    rclcpp::shutdown();

    return 0;
}