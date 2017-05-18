#include <crawler_tags_detector_node.h>


CCrawlerTagsDetector::CCrawlerTagsDetector(ros::NodeHandle &nh)
{

	scale_bias_ = 0.7;	
    // Subscribe to the marker pose publisher
    this->markers_pose_ = nh.subscribe ("/alvar_input", 1, &CCrawlerTagsDetector::markerCallback, this);

    // Publish the Stamped Pose
    this->pose_pub_ = nh.advertise<geometry_msgs::PoseStamped>("/pose_output", 100);
    nh.param<std::string>("output_frame", camera_frame_id_, "cam");

}

void CCrawlerTagsDetector::markerCallback (const ar_track_alvar_msgs::AlvarMarkers& pose_Markers)
{
	// Take the array of alvarMarker
	arPoseMarkers_ = pose_Markers;

	    if(arPoseMarkers_.markers.size() > 0)

	    {

		    arPoseMarker_ = arPoseMarkers_.markers[0];

		 	geometry_msgs::PoseStamped pose_msg;
		    pose_msg.header.stamp = arPoseMarker_.header.stamp;
		    pose_msg.header.frame_id = camera_frame_id_;

		    pose_msg.pose.position.x = arPoseMarker_.pose.pose.position.x*scale_bias_;
		    pose_msg.pose.position.y = arPoseMarker_.pose.pose.position.y*scale_bias_;
		    pose_msg.pose.position.z = arPoseMarker_.pose.pose.position.z*scale_bias_;

		    pose_msg.pose.orientation.x = arPoseMarker_.pose.pose.orientation.x*scale_bias_;
		    pose_msg.pose.orientation.y = arPoseMarker_.pose.pose.orientation.y*scale_bias_;
		    pose_msg.pose.orientation.z = arPoseMarker_.pose.pose.orientation.z*scale_bias_;
		    pose_msg.pose.orientation.w = arPoseMarker_.pose.pose.orientation.w*scale_bias_;

		    if(pose_msg.pose.position.z > 0.0)
		    {
		    	pose_pub_.publish(pose_msg);
	    	}
	    	
	    }




}

void CCrawlerTagsDetector::MainNodeFc()
{



}


int main(int argc, char** argv)
{
    ros::init(argc, argv, ros::this_node::getName());
    ros::NodeHandle nh(ros::this_node::getName());
    ros::Rate loop_rate(50);

    CCrawlerTagsDetector crawler_tags_detector(nh);

    while (ros::ok()) {
        crawler_tags_detector.MainNodeFc();
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}