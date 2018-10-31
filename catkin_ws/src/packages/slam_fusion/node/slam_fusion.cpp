#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


#include <ros/ros.h>
#include <ros/console.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>


#define POSE_TOPIC_NAMES "sptam/robot/pose,estimate/active_path,camera_pose"

class SlamFusion {

private:

    ros::NodeHandle nh;

    std::vector<nav_msgs::Path> paths;
    std::vector<bool> get_latest_pose_;
	bool existAllPose();
	std::string pose_topic_names;



public:

	// Functions

	void initialize(ros::NodeHandle _nh);
	void callback_ndt_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);
	void callback_limo_path(const nav_msgs::Path::ConstPtr& msg);
	void callback_orb_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);

	void fusion();

	std::vector<std::string> getPoseTopicNames();

};

void SlamFusion::initialize(ros::NodeHandle _nh) {

    ROS_INFO("Initialize slam_fusion");

    nh=_nh;
    paths.resize(3);
    get_latest_pose_=std::vector<bool>(3,false);

    if(!nh.getParam("pose_topic_names",pose_topic_names)){
        pose_topic_names=POSE_TOPIC_NAMES;
    }

}

void SlamFusion::callback_ndt_pose(const geometry_msgs::PoseStamped::ConstPtr &msg) {

    std::string str=getPoseTopicNames()[0];
    ROS_DEBUG_STREAM("callback "<<str);

	paths[0].poses.push_back(*msg);
	get_latest_pose_[0]=true;
	if(existAllPose()){
	    fusion();
	}
}

void SlamFusion::callback_limo_path(const nav_msgs::Path::ConstPtr &msg) {

    std::string str=getPoseTopicNames()[1];
    ROS_DEBUG_STREAM("callback "<<str);
    ROS_DEBUG_STREAM("size of pose in limo_path: "<<msg->poses.size());

    paths[1]=*msg;
    get_latest_pose_[1]=true;
    if(existAllPose()){
        fusion();
    }
}

void SlamFusion::callback_orb_pose(const geometry_msgs::PoseStamped::ConstPtr &msg) {

    std::string str=getPoseTopicNames()[2];
    ROS_DEBUG_STREAM("callback "<<str);

    paths[2].poses.push_back(*msg);
    get_latest_pose_[2]=true;
    if(existAllPose()){
        fusion();
    }

}

bool SlamFusion::existAllPose() {
    auto itr=std::find(get_latest_pose_.begin(),get_latest_pose_.end(),false);
    if(itr==get_latest_pose_.end()){
        ROS_DEBUG_STREAM("Getting All Packages' Pose");
        get_latest_pose_=std::vector<bool>(3,false);
        return true;
    }
    else{
        ROS_DEBUG_STREAM("Non exist: ");
        ROS_DEBUG_STREAM(pose_topic_names<<get_latest_pose_[0]<<get_latest_pose_[1]<<get_latest_pose_[2]);
        return false;
    }

}

void SlamFusion::fusion() {
    ROS_INFO("Fuse Poses");


}


/*
 * PoseのTopic名をsplit
 */
std::vector<std::string> SlamFusion::getPoseTopicNames() {
    std::vector<std::string> out;
    std::string item;
    for (char ch: pose_topic_names) {
        if (ch == ',') {
            if (!item.empty())
                out.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        out.push_back(item);

    return out;
}



// -----------------------------------
//	Main Function
// -----------------------------------
int main(int argc, char** argv) {

    // debug mode
    if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
        ros::console::notifyLoggerLevelsChanged();
    }

	// Initialize ROS
	ros::init(argc, argv, "slam_fusion");
	ros::NodeHandle nh;

	SlamFusion fusion;
	fusion.initialize(nh);

	std::vector<std::string> topic_names=fusion.getPoseTopicNames();

	ros::Subscriber sub_ndt_pose = nh.subscribe(topic_names[0], 1, &SlamFusion::callback_ndt_pose, &fusion);
	ros::Subscriber sub_limo_pose = nh.subscribe(topic_names[1], 1, &SlamFusion::callback_limo_path, &fusion);
	ros::Subscriber sub_orb_pose = nh.subscribe(topic_names[2], 1, &SlamFusion::callback_orb_pose, &fusion);

	ros::spin();

	return (0);
}
