#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "gaggum_msgs/msg/test.hpp"
#include "gaggum_msgs/msg/detection.hpp"
#include "nav_msgs/msg/odometry.hpp"

using namespace std::chrono_literals;
using namespace std;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", 10);
      pub_ = this->create_publisher<gaggum_msgs::msg::Detection>("yolo", 100);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      cout << "timer" << '\n';
      // auto message = gaggum_msgs::msg::Test();
      // auto my_msg = gaggum_msgs::msg::Detection();
      auto odom_msg = nav_msgs::msg::Odometry();
      odom_msg.pose.pose.position.x = 0.0;
      odom_msg.pose.pose.position.y = 0.0;
      odom_msg.pose.pose.position.z = 0.0;

      // message.num = this -> count_++;
      // my_msg.num_index = 12;

      // RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
      publisher_->publish(odom_msg);
      // pub_->publish(my_msg);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_; 
    rclcpp::Publisher<gaggum_msgs::msg::Detection>::SharedPtr pub_; 
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}