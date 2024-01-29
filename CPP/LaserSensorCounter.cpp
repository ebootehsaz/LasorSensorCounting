#include <algorithm>  //TODO: check that all the includes are needed
#include <cmath>
#include <functional>
#include <memory>
#include <queue>
#include <ranges>
#include <vector>

#include "constants.hpp"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class LaserSensorCounter : public rclcpp::Node {
private:
    int sensor_pin;
    int counter;
    bool object_detected;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr counter_pub;
    rclcpp::TimerBase::SharedPtr timer_;
    int laser_din=sensor_pin;

    void checkSensor() {
        // A senior programmer needs to verify this if check to check the sensor and update `object_detected` and `counter`
        if (digitalRead(laser_din)==LOW) {
            if (!object_detected) {
                object_detected = true;
                counter++;
                if (counter > 4) counter = 4; // Limit the count
                counter_pub->publish(counter);
            }
        } else {
            object_detected = false;
        }
    }

public:
    LaserSensorCounter(int sensor_pin) : Node("laser_sensor_counter"), sensor_pin(sensor_pin), counter(0), object_detected(false) {
        counter_pub = this->create_publisher<std_msgs::msg::Int32>("laser_sensor_count", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&LaserSensorCounter::checkSensor, this));
    }

    void resetCounter() {
        counter = 0;
        counter_pub->publish(counter);
    }
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    // auto node = std::make_shared<LaserSensorCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}