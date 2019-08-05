#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "ackermann_msgs/AckermannDrive.h"
#include <sstream>
#include <iostream>   // std::cout
#include <string> 

class TwistToAackermann {
    public:
        TwistToAackermann()
        {
        //Topic you want to publish
        pub_ = n_.advertise<ackermann_msgs::AckermannDrive>("/rbcar_robot_control/command", 1);

        //Topic you want to subscribe
        sub_ = n_.subscribe("/twist_to_ackermannStamp", 1, &TwistToAackermann::callback, this);
        }

        void callback(const geometry_msgs::Twist& msg) {

            float baseLength = 0.333;

            ackermann_msgs::AckermannDrive out;
            ackermann_msgs::AckermannDrivePtr stamp; 
            out.speed = msg.linear.x; 
            if (msg.angular.z==0) {
                out.steering_angle = 0;
            }
            else {
                out.steering_angle = baseLength/(msg.linear.x/msg.angular.z);
            } 

            stamp.Ackermandrive = out; 
            pub_.publish(stamp); 
        }
    private:
        ros::NodeHandle n_;
        ros::Publisher pub_;
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
