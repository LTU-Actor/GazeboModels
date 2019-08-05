#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "ackermann_msgs/AckermannDrive.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include <sstream>
#include <iostream>   // std::cout
#include <string> 

class TwistToAackermann {
    public:
        TwistToAackermann()
        {
        //Topic you want to publish
        pubAD_ = n_.advertise<ackermann_msgs::AckermannDrive>("/ackermann_cmd", 1);
        pubADS_ = n_.advertise<ackermann_msgs::AckermannDriveStamped>("/rbcar_robot_control/command", 1);

        //Topic you want to subscribe
        sub_ = n_.subscribe("/twist_to_ackermann", 1, &TwistToAackermann::callback, this);
        }

        void callback(const geometry_msgs::Twist& msg) {

            float baseLength = 1.75;

            ackermann_msgs::AckermannDrive ad;
            ackermann_msgs::AckermannDriveStamped ads;  
            ad.speed = msg.linear.x; 
            if (msg.angular.z==0) {
                ad.steering_angle = 0;
            }
            else {
                ad.steering_angle = baseLength/(msg.linear.x/msg.angular.z);
            } 

            ads.header.stamp = ros::Time::now(); 
            ads.drive.jerk = 0.0; 
            ads.drive.acceleration = 0.0; 
            ads.drive.steering_angle_velocity = 0.0;
            ads.drive.steering_angle = ad.steering_angle; 
            ads.drive.speed = msg.linear.x; 

            pubADS_.publish(ads); 
            pubAD_.publish(ad); 
        }
    private:
        ros::NodeHandle n_;
        ros::Publisher pubAD_;
        ros::Publisher pubADS_;
        ros::Subscriber sub_;
};
// void ackermanCallback(const ackermann_msgs::AckermannDrivePtr& str) {
//     ros::init(argc, argv, "twist_to_ackermann");
//     ros::NodeHandle n; 

//     ros::Publisher ackermann_pub = 
//         n.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd",1000);
//     ros::Rate loop_rate(10); 
// }

int main(int argc, char **argv) {
    ros::init(argc, argv, "twist_to_ackermann");

    TwistToAackermann SAPObject; 
    ros::spin(); 

    //ros::NodeHandle n; 

    // ros::Publisher ackermann_pub = 
    //     n.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd",1000);
    // ros::Rate loop_rate(10); 

    //int count=0;

    // while (ros::ok()) {
    //     ackermann_msgs::AckermannDrive msg;

    //     msg.steering_angle = 0.0; 
    //     msg.steering_angle_velocity = 1.0;
    //     msg.speed = 1.0; 
    //     msg.acceleration = 1.0; 
    //     msg.jerk = 0.0;  

    //     //std::cout << msg.data.c_str(); 
    //     //ROS_INFO("%s", msg.data.c_str()); 

    //     ackermann_pub.publish(msg); 
    //     ros::spinOnce(); 
    //     loop_rate.sleep();
    //     ++count; 
    // }
    return 0; 
}
