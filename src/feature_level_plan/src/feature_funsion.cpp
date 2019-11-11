#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/point_cloud_conversion.h>

//订阅和发布的节点
ros::Publisher scan_funsion_pub;
ros::Subscriber scan_front_sub;
ros::Subscriber scan_back_sub;

void scanFrontCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    scan_funsion_pub.publish(msgs);
}

void scanBackCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    /*sensor_msgs::LaserScan scan;
    scan.header.frame_id = "hokuyo_link_front";
    scan.header.stamp =  ros::Time::now();
    scan.angle_min = msgs->angle_min;
    scan.angle_max = msgs->angle_max;
    scan.angle_increment = msgs->angle_increment;
    scan.time_increment = msgs->time_increment;
    scan.ranges = msgs->ranges;
    scan.intensities = msgs->intensities;
    scan.range_min = msgs->range_min;
    scan.range_max = msgs->range_max;*/
    scan_funsion_pub.publish(msgs);
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "data_funsion");
    ros::NodeHandle n;
    //tfListener_->setExtrapolationLimit(ros::Duration(0.1));
    scan_front_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_front",5,scanFrontCallback);
    scan_back_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_back",5,scanBackCallback);
    scan_funsion_pub = n.advertise<sensor_msgs::LaserScan>("/scan", 5);

    ros::spin();
}