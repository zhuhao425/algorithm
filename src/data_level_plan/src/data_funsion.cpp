#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <data_level_plan/ScanMerge.h>
//#include <iostream>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/point_cloud_conversion.h>

//订阅和发布的节点
ros::Publisher scan_funsion_pub;
ros::Subscriber scan_front_sub;
ros::Subscriber scan_back_sub;

//中间数据，LaserScan需转换为点云进行拼接
sensor_msgs::PointCloud2 front_data;
sensor_msgs::PointCloud2 back_data;
bool front=false;
bool back=false;

//LaserScan的配置
struct configs{
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;
    std::string frame_id;
    ros::Time stamp;
};

configs conf;


tf::TransformListener* tfListener_;
laser_geometry::LaserProjection* projector_;

void funsion_data()
{
    //ROS_INFO("begin to funsion");
    front = false;
    back = false;
    //ROS_INFO("funsion data : %f %f",conf.angle_increment,conf.time_increment);
    ScanMerge scanMerge = ScanMerge(front_data,back_data,conf.angle_increment,conf.time_increment,conf.scan_time,conf.range_min,conf.range_max,conf.frame_id,conf.stamp);
    //ROS_INFO("created a scanMerge instance");
    sensor_msgs::LaserScan output = scanMerge.merge();//将两个点云拼接后根据LaserScan的angle_min,angle_max,angle_incrmement转换成LaserScan
    scan_funsion_pub.publish(output);
}

void scanFrontCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    conf.angle_increment = msgs->angle_increment;
    conf.time_increment = msgs->time_increment;
    //ROS_INFO("front:%f %f",msgs->angle_max,msgs->angle_min);
    conf.scan_time = msgs->scan_time;
    conf.range_min = msgs->range_min;
    conf.range_max = msgs->range_max;
    conf.frame_id = msgs->header.frame_id;
    conf.stamp = msgs->header.stamp;
    sensor_msgs::PointCloud tmpCloud1,tmpCloud2;
    tfListener_->waitForTransform("map", "/base_footprint", msgs->header.stamp, ros::Duration(1));
    projector_->transformLaserScanToPointCloud(msgs->header.frame_id, *msgs, tmpCloud1, *tfListener_);
    try
    {
        tfListener_->transformPointCloud("/base_footprint", tmpCloud1, tmpCloud2);//将激光雷达转换成的点云tmpCloud1通过tf转换到merge_link并发布为tmpCloud2
    }catch (tf::TransformException ex)
    {
        ROS_ERROR("%s",ex.what());
        return;
    }
    sensor_msgs::convertPointCloudToPointCloud2(tmpCloud2,front_data);
    front = true;
    //ROS_INFO("front ready");
    if(front && back)
        funsion_data();
}

void scanBackCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    //ROS_INFO("back:%f %f",msgs->angle_max,msgs->angle_min);
    sensor_msgs::PointCloud tmpCloud1,tmpCloud2;
    tfListener_->waitForTransform("map", "/base_footprint", msgs->header.stamp, ros::Duration(1));
    projector_->transformLaserScanToPointCloud(msgs->header.frame_id, *msgs, tmpCloud1, *tfListener_);
    try
    {
        tfListener_->transformPointCloud("/base_footprint", tmpCloud1, tmpCloud2);//将激光雷达转换成的点云tmpCloud1通过tf转换到merge_link并发布为tmpCloud2
    }catch (tf::TransformException ex)
    {
        ROS_ERROR("%s",ex.what());
       return;
    }
    sensor_msgs::convertPointCloudToPointCloud2(tmpCloud2,back_data);
    back = true;
    //ROS_INFO("back ready");
    if(front && back)
        funsion_data();
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "data_funsion");
    ros::NodeHandle n;
    //tfListener_->setExtrapolationLimit(ros::Duration(0.1));
    scan_front_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_front",5,scanFrontCallback);
    scan_back_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_back",5,scanBackCallback);
    scan_funsion_pub = n.advertise<sensor_msgs::LaserScan>("/scan", 5);

    tf::TransformListener tftmp;
    laser_geometry::LaserProjection projectiontmp;
    tfListener_ = &tftmp;
    projector_ = &projectiontmp;
    ros::spin();
}