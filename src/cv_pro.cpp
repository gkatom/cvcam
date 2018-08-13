#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <std_msgs/String.h>


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  { cv::Mat greyMat;
    cv::Mat colorMat=cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::cvtColor(colorMat, greyMat, CV_BGR2GRAY);
    //cv::imshow("view", greyMat);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_process");
  ros::NodeHandle nh;
 // cv::namedWindow("view");
 // cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("cv_camera/image_raw", 1, imageCallback);
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("instruction/vision", 100);
  while (ros::ok())
  {
   std_msgs::String msg;
   msg.data = "Test";
   chatter_pub.publish(msg);
   ros::spinOnce();
  }

  cv::destroyWindow("view");
}

