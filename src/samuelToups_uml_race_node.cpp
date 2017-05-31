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

//  ROS_INFO("before spin");

  // find the greatest concentration of high range values
  // find the approximate middle of the grouping
  // rotate to face the opening

  // move forward

//  for (float i = msg->angle_min; i < msg->angle_max; i+=msg->angle_increment)
//    {
//
//    }
//  int i = 0;
//  while (msg->ranges[i] != msg->range_max)
//  {
//    i++;
//  }

/*  int max_index = 0;
  int index = 0;
  float max_range = 0;
  float angle = msg->angle_min;
  float high_count = 0;
  float high_count_max = 0;
  for (float i = msg->angle_min; i < msg->angle_max; i+=msg->angle_increment)
  {
    if (msg->ranges[index] > msg->range_max/2)
    {
      high_count++;
      if (high_count > high_count_max)
      {
        high_count_max = high_count;
        max_index = index;
      }
    }
    else
    {
      high_count = 0;
    }
    index++;
  }
*/

//  double rotate_amount = msg->angle_min + i*msg->angle_increment;
/*  double rotate_amount;
  if ((msg->angle_min + max_index*msg->angle_increment) <= -20)
  {
    rotate_amount = -20;
  }
  else if ((msg->angle_min + max_index*msg->angle_increment) > 20)
  {
    rotate_amount = 0;
  }
  else //angle is greater than 0
  {
    rotate_amount = 20;
  }*/

  geometry_msgs::Vector3 move_linear;
  move_linear.x = 5;

  double rotate_amount = 0;
/*  if (msg->ranges[(int ((msg->angle_max - msg->angle_min) / msg->angle_increment) / 2)] > msg->range_max * .8)
  {
    rotate_amount = 0;
  }
  else*/ if (msg->ranges[(int ((msg->angle_max - msg->angle_min) / msg->angle_increment) / 2) + 50] < msg->range_max / 3)
  {
    rotate_amount = -3200;
    move_linear.x = 1;

  }
  else if (msg->ranges[(int ((msg->angle_max - msg->angle_min) / msg->angle_increment) / 2) - 50] < msg->range_max / 3)
  {
    rotate_amount = 3200;
    move_linear.x = 1;
  }
  else if (msg->ranges[0] < msg->range_max / 3)
  {
    rotate_amount = 1600;
  }
  else if (msg->ranges[(int (msg->angle_max - msg->angle_min / msg->angle_increment))] < msg->range_max / 3)
  {
    rotate_amount = -1600;
  }


  geometry_msgs::Vector3 rotate_angular;
  rotate_angular.z = rotate_amount;
  move.angular = rotate_angular;
  move.linear = move_linear;

  movePub.publish(move);
}

int main(int argc, char** argv)
{
//  printf("start of main");

  ros::init(argc, argv, "race_solver");

  ros::NodeHandle n;

  movePub = n.advertise<geometry_msgs::Twist>("/robot/cmd_vel", 1000);
  sub = n.subscribe("/robot/base_scan", 1000, movementCallback);

//  ROS_INFO("before spin");

  ros::spin();

  return 0;
}
