ackermann_vehicle
=================

ROS packages for simulating a vehicle with Ackermann steering

Clone the repository into the src folder (or sub folder) of your catkin workspace.

$> git clone https://github.com/LTU-Actor/GazeboSimulatorModel.git

Clone the velodyne_simulator into the same src. 

$> git clone https://github.com/florianshkurti/velodyne_simulator.git

Install needed ackerman packages

$> sudo apt-get install ros-kinetic-ackermann-msgs
$> sudo apt-get install ros-kinetic-ackermann-steering-controller

Make sure controller packages are installed

sudo apt-get install ros-kinetic-joint-state-controller  
sudo apt-get install ros-kinetic-effort-controllers  
sudo apt-get install ros-kinetic-position-controllers

In the main catkin directory, run catkin_make.

You may also need to install libignition-math2-dev to get a file used by the Velodyne plugins, Inertial.hh. If you get the following error:

[workspace]/src/GazeboSimulatorModel/velodyne_gazebo_plugins/src/GazeboRosVelodyneLaser.cpp:35:
/usr/include/gazebo-7/gazebo/msgs/msgs.hh:24:37: fatal error: ignition/math/Inertial.hh: No such file or directory

Run the following to install the library: 

$> sudo apt-get install libignition-math2-dev

Setup the terminal.

$> source devel/setup.sh

Run either the ackermann vehicle with only the cammera, or with LiDAR as well. 

roslaunch ackermann_vehicle_gazebo ackermann_vehicle.launch
roslaunch ackermann_vehicle_gazebo ackermann_vehicle_lidar.launch


