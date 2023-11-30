#!/usr/bin/env python

import RPi.GPIO as GPIO
import rospy
from std_msgs.msg import Int32

class LaserSensorCounter:
    def __init__(self, sensor_pin):
        self.sensor_pin = sensor_pin
        self.counter = 0
        self.object_detected = False
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.sensor_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        self.pub = rospy.Publisher('laser_sensor_counter', Int32, queue_size=10)

    def update_counter(self):
        if GPIO.input(self.sensor_pin) == 0: # Assuming 0 means the object is detected
            if not self.object_detected:  # If previous state was "not detected"
                self.counter += 1  # Increment the counter
                self.pub.publish(self.counter)
            self.object_detected = True
        else:
            self.object_detected = False

    def run(self):
        rospy.init_node('laser_sensor_counter_node', anonymous=True)
        rate = rospy.Rate(10) # 10Hz
        while not rospy.is_shutdown():
            self.update_counter()
            rate.sleep()

if __name__ == '__main__':
    sensor_pin = 18  # Replace with the correct pin number
    laser_sensor_counter = LaserSensorCounter(sensor_pin)
    try:
        laser_sensor_counter.run()
    except rospy.ROSInterruptException:
        GPIO.cleanup()
