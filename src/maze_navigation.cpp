#include "ros/ros.h"
#include "libs/robot.h"
#include <sstream>

int main(int argc, char *argv[]) {  
  ros::init(argc, argv, "maze_navigation");

  ros::NodeHandle nh;
  Robot robot = Robot(&nh);

  robot.startNavigation();

  return 0;  
}