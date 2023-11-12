#include "LaserSensorCounter.h"

LaserSensorCounter::LaserSensorCounter(ros::NodeHandle* nh, int pin) : sensor_pin(pin), counter(0), object_detected(false) {
    wiringPiSetupGpio(); // Use Broadcom pin numbering
    pinMode(sensor_pin, INPUT);
    pullUpDnControl(sensor_pin, PUD_UP); // Enable pull-up resistor
    counter_pub = nh->advertise<std_msgs::Int32>("laser_sensor_counter", 10);
}

void LaserSensorCounter::checkSensor() {
    if (digitalRead(sensor_pin) == LOW) { // LOW when laser is interrupted
        if (!object_detected) {
            counter++;
            std_msgs::Int32 msg;
            msg.data = counter;
            counter_pub.publish(msg);
        }
        object_detected = true;
    } else {
        object_detected = false;
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "laser_sensor_counter");
    ros::NodeHandle nh;
    LaserSensorCounter lsc(&nh, 18); // Change the pin number accordingly

    ros::Rate loop_rate(10); // Loop at 10Hz
    while (ros::ok()) {
        lsc.checkSensor();
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
