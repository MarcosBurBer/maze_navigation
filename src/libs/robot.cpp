#include "robot.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <math.h>

Robot::Robot(ros::NodeHandle *nh) {  
  turtlebot_pub = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 100);
  laser = new Laser(nh); 
  odom_sub = nh->subscribe("odom", 1000, &Robot::robotOdomCallback, this);
  state = rs_still;
}

void Robot::startNavigation() { 
  
  ros::Rate loop_rate(10); 
  float collision = 0;
 
  while (ros::ok()) {
    switch(state)
   {
    case rs_still: 
      
      state = rs_moving;
      gap_delay = 100;
      break;

    case rs_moving:
      collision = laser->forwardCollisionDistance();
      ROS_INFO("Distance to collision: %f", collision);

          if (collision> 0.8){
            Robot::goForward();
            }
            else if (collision > 0.65 && collision < 0.8){
              Robot::rotateRight();
              }
              else if (collision > 0.4 && collision < 0.65 ){
              Robot::rotateLeft();
              }
            else if (collision < 0.4 ){
              Robot::goBackward();
            }

      loop_rate.sleep();
      ros::spinOnce();
      ROS_INFO("moving distance : %f",collision);
      state = rs_collision;
      break; 
      
    case rs_collision: 
      state = rs_backward;
      ROS_INFO("Collision");
      
      break; 

    case rs_backward: 
     
      Robot::goBackward();
 
      state = rs_still;
      
      break;
   }
  }
}


void Robot::goForward() { 
  geometry_msgs::Twist movegoForwardMsg;
   movegoForwardMsg.linear.x = 0.4;
  
   turtlebot_pub.publish(movegoForwardMsg);  
}
void Robot::rotateLeft() { 
  geometry_msgs::Twist rotateLeft;
    rotateLeft.linear.x = 0.1;
    rotateLeft.angular.z =  -M_PI/5;
  
   turtlebot_pub.publish(rotateLeft);  
}

void Robot::rotateRight() { 
  geometry_msgs::Twist rotateRight;
  rotateRight.linear.x = 0.1;
  rotateRight.angular.z =  -M_PI/5;
  turtlebot_pub.publish(rotateRight);
}


void Robot::goBackward() {
  geometry_msgs::Twist backward;
  backward.linear.x = -0.4;
  backward.angular.z = -M_PI/2;
  
  turtlebot_pub.publish(backward);
}
 

  void Robot::robotOdomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
   ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", 
   msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);

   float x_curr = msg-> pose.pose.position.x;
   float y_curr = msg-> pose.pose.position.y;

    if(state == rs_moving){
     
     if (gap_delay > 0){
       gap_delay --;
     }
     double distance = (x_prev - x_curr)*(x_prev - x_curr) + (y_prev - y_curr)*(y_prev - y_curr);
     ROS_INFO("moving distance : [%f]",distance);
     if(distance < 0.000001 && gap_delay <= 0){
      state =rs_collision;
      }
    }
   x_prev = msg-> pose.pose.position.x;
   y_prev = msg-> pose.pose.position.y;
}