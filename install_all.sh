#!/bin/bash

cd `dirname $0`

sudo apt-get update

cd withous_catkin/
sh install_limo.sh
sh install_orbslam.sh

cd ../

cd catkin_ws/src/
sh install_sptam.sh

