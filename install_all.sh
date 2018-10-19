#!/bin/bash

cd `dirname $0`

sudo apt-get update

echo "\\/-----　　 Install Autoware　　　-----/\\"
sudo apt-get install -y python-catkin-pkg python-rosdep python-wstool ros-$ROS_DISTRO-catkin libmosquitto-dev gksu
cd Autoware/ros/src
catkin_init_workspace
cd ../
rosdep install -y --from-paths src --ignore-src --rosdistro $ROS_DISTRO
./catkin_make_release

cd ../

cd withous_catkin/
sh install_limo.sh
sh install_orbslam.sh

cd ../

cd catkin_ws/src/
sh install_sptam.sh

