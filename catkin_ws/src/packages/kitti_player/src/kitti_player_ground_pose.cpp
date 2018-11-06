//
// Created by ohashi on 18/11/06.
//

#include <iostream>

#include <ros/ros.h>
#include <ros/console.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>
#include <opencv2/core/core.hpp>


/**
 * Main Funciton
**/

class PosePublisher {

private:
    ros::NodeHandle nh;

    geometry_msgs::PoseStamped pose;
    nav_msgs::Path path;

public:


};

int main(int argc, char **argv) {

    // debug mode
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug)) {
        ros::console::notifyLoggerLevelsChanged();
    }

    // Initialize ROS
    ros::init(argc, argv, "kitti_player_ground_truth");
    ros::NodeHandle nh;

    while(true){
        ros::Time time=ros::Time::now();
        std::cout<<time<<std::endl;
        cv::waitKey(10);
    }





//    SlamFusion fusion;
//    fusion.initialize(nh);
//
//    std::vector<std::string> topic_names = fusion.getPoseTopicNames();
//
//    ros::Subscriber sub_ndt_pose = nh.subscribe(topic_names[0], 1, &SlamFusion::callback_sptam, &fusion);
//    ros::Subscriber sub_limo_pose = nh.subscribe(topic_names[1], 1, &SlamFusion::callback_limo_path, &fusion);
//    ros::Subscriber sub_orb_pose = nh.subscribe(topic_names[2], 1, &SlamFusion::callback_orb_pose, &fusion);
//    ros::Subscriber sub_groundtruth = nh.subscribe(GROUNDTRUTH_TOPIC_NAME, 1, &SlamFusion::callback_groundtruth, &fusion);

//    ros::spin();

    return (0);
}