#!/bin/bash

#new terminal 1
xterm -e bash -c 'roscore' &
sleep 1

#new terminal 2
xterm -e bash -c 'cd ~/localization_kitti_ws/catkin_ws; source devel/setup.bash; rosrun mypkg param_optimization' &
sleep 5

current_sequence=$(rosparam get /current_sequence)


