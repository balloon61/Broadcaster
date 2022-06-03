#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>



void poseCallback(const nav_msgs::Odometry::ConstPtr& odomsg)
{
   //TF odom=> base_link
    
     static tf::TransformBroadcaster odom_broadcaster;
    odom_broadcaster.sendTransform(
      tf::StampedTransform(
				tf::Transform(tf::Quaternion(odomsg->pose.pose.orientation.x,
                                     odomsg->pose.pose.orientation.y,
                                     odomsg->pose.pose.orientation.z,
                                     odomsg->pose.pose.orientation.w),
        tf::Vector3(odomsg->pose.pose.position.x, 
                    odomsg->pose.pose.position.y, 
                    odomsg->pose.pose.position.z)),
				odomsg->header.stamp, "map", "odom"));

}




int main(int argc, char** argv){
	ros::init(argc, argv, "mavros_tf");
	ros::NodeHandle n;

	ros::Rate r(20);

	tf::TransformBroadcaster broadcaster;
  

	ros::Subscriber pose_sub = n.subscribe<nav_msgs::Odometry>("/mavros/odometry/in", 1, poseCallback);

	while(n.ok()){


    ros::spin();		
    r.sleep();
	}
}				


