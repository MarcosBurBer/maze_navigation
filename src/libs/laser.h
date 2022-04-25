#ifndef MAZE_NAVIGATION_LASER_H
#define MAZE_NAVIGATION_LASER_H

#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>

class Laser {
    public:
        Laser(ros::NodeHandle *nh);
        float forwardCollisionDistance();
    private:
        ros::Subscriber laser_sub;
        float forwardDistance;
        void laserScanCallback(
          const sensor_msgs::LaserScan::ConstPtr& msg);
};

#endif