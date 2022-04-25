#include "laser.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/LaserScan.h>

Laser::Laser(ros::NodeHandle *nh) {
    laser_sub = nh->subscribe("/scan", 1000, &Laser::laserScanCallback, this);
}

float Laser::forwardCollisionDistance() {    
    return forwardDistance;
}

void Laser::laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    forwardDistance = msg->ranges[0];    
}