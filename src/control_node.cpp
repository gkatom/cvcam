#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

void visionCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard from vision: [%s]", msg->data.c_str());
}
void joystickCallback(const geometry_msgs::Twist& msg)
{
  ROS_INFO_STREAM("I heard from joystick:"<<" linear="<<msg.linear.x<<" angular="<<msg.angular.z);

}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "control_node");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("instruction/vision", 100, visionCallback);
    ros::Subscriber sub2 = n.subscribe("instruction/joystick", 1000, joystickCallback);
    ros::Publisher velPub = n.advertise<geometry_msgs::Twist>("motor_cmd", 1);
    //ros::Rate loop_rate(20);
    geometry_msgs::Twist msg;
    while (ros::ok())
    {
        msg.linear.x = 1;
        velPub.publish(msg);
        ros::spinOnce();
    }
    //ros::spin();
    return 0;

}