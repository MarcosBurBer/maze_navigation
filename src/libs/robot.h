#ifndef MAZE_NAVIGATION_ROBOT_H
#define MAZE_NAVIGATION_ROBOT_H

#include "ros/ros.h"
#include "laser.h"
#include "nav_msgs/Odometry.h"

enum RobotState {rs_still, rs_moving, rs_collision, rs_backward};

class Robot {
    public:
        Robot(ros::NodeHandle *nh);
        void startNavigation();
    private:
        Laser* laser;
        ros::Subscriber odom_sub;
        ros::Publisher turtlebot_pub;
        RobotState state;
        float x_prev; 
        float y_prev;
        float z_prev;
        int gap_delay;
        void robotOdomCallback(const nav_msgs::Odometry::ConstPtr& msg);
        void goForward();
        void rotateRight();
        void rotateLeft();
        void goBackward();
};

#endif