#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

ros::Publisher movePub;
ros::Subscriber sub;

// linear is x only
// angular is z only

void movementCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  geometry_msgs::Twist move;

  // find the greatest concentration of high range values
  // find the approximate middle of the grouping
  // rotate to face the opening
  // move forward

//  for (float i = msg->angle_min; i < msg->angle_max; i+=msg->angle_increment)
//    {
//
//    }
  int i = 0;
  while (msg->ranges[i] != msg->range_max)
  {
    i++;
  }

//  double rotate_amount = msg->angle_min + i*msg->angle_increment;
  double rotate_amount;
  if ((msg->angle_min + i*msg->angle_increment) <= -20)
  {
    rotate_amount = -200;
  }
  else if ((msg->angle_min + i*msg->angle_increment) > 20)
  {
    rotate_amount = 0;
  }
  else //angle is greater than 0
  {
    rotate_amount = 200;
  }
  rotate_amount *= 1000;
  geometry_msgs::Vector3 rotate_angular;
  rotate_angular.z = rotate_amount;
  move.angular = rotate_angular;
  geometry_msgs::Vector3 move_linear;
  move_linear.x = 1;
  move.linear = move_linear;

  movePub.publish(move);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "race_solver");

  ros::NodeHandle n;

  movePub = n.advertise<geometry_msgs::Twist>("/robot/cmd_vel", 1000);
  sub = n.subscribe("/robot/base_scan", 1000, movementCallback);


  ros::spin();

  return 0;
}
