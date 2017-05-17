#ifndef _CRAWLER_TAGS_DETECTOR_H_
#define _CRAWLER_TAGS_DETECTOR_H_

#include <ros/ros.h>

#include <string>

#include <geometry_msgs/PoseStamped.h>
#include <string>

#include <mutex.h>
#include <mutex_exceptions.h>


#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>


class CCrawlerTagsDetector
{
public:
    CCrawlerTagsDetector(ros::NodeHandle& nh);


    void MainNodeFc(void);	



private:

    ar_track_alvar_msgs::AlvarMarker arPoseMarker_;

	ar_track_alvar_msgs::AlvarMarkers arPoseMarkers_;

	double scale_bias_;
    ros::NodeHandle nh;
    ros::Publisher pose_pub_;

    ros::Subscriber markers_pose_;

    std::string camera_frame_id_;

    void markerCallback (const ar_track_alvar_msgs::AlvarMarkers & pose_Markers);

    

};

#endif