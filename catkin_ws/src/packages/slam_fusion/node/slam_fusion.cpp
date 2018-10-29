#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


#include <ros/ros.h>
#include <ros/console.h>
#include <geometry_msgs/PoseStamped.h>

class SlamFusion {

private:
	std::vector<geometry_msgs::PoseStamped> poses[3];
	float moving_distance[3];




public:

	// Functions

	void initialize(ros::NodeHandle _nh);
	void callback_ndt_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);
	void callback_limo_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);
	void callback_orb_pose(const geometry_msgs::PoseStamped::ConstPtr& msg);


};

void SlamFusion::initialize(ros::NodeHandle _nh) {
	moving_distance[0]=moving_distance[1]=moving_distance[2]=0.0;
}

void SlamFusion::callback_ndt_pose(const geometry_msgs::PoseStamped::ConstPtr &msg) {
	poses[0].push_back(*msg);
	moving_distance[0]+=
}

void SlamFusion::callback_limo_pose(const geometry_msgs::PoseStamped::ConstPtr &msg) {
	poses[1].push_back(*msg);
}

void SlamFusion::callback_orb_pose(const geometry_msgs::PoseStamped::ConstPtr &msg) {
	poses[2].push_back(*msg);
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

	ros::Subscriber sub_ndt_pose = nh.subscribe("ndt_pose", 1, &SlamFusion::callback_ndt_pose, &fusion);
	ros::Subscriber sub_limo_pose = nh.subscribe("limo_pose", 1, &SlamFusion::callback_limo_pose, &fusion);
	ros::Subscriber sub_orb_pose = nh.subscribe("orb_pose", 1, &SlamFusion::callback_orb_pose, &fusion);

	ros::spin();

	return (0);
}
