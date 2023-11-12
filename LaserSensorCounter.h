#ifndef LASER_SENSOR_COUNTER_H
#define LASER_SENSOR_COUNTER_H

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <wiringPi.h>

class LaserSensorCounter {
private:
    int sensor_pin;
    int counter;
    bool object_detected;
    ros::Publisher counter_pub;

public:
    LaserSensorCounter(ros::NodeHandle* nh, int pin);
    void checkSensor();
};

#endif // LASER_SENSOR_COUNTER_H
