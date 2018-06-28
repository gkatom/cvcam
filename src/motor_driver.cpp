#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


void motor_control(const geometry_msgs::Twist& msg)
{
  ROS_INFO_STREAM("I heard from joystick:"<<" linear="<<msg.linear.x<<" angular="<<msg.angular.z);

}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "motor_driver");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("motor_cmd", 1, motor_control);
    ros::spin();
    return 0;

}