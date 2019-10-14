
#include <Eigen/Dense>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include "pcl_ros/point_cloud.h"

class ScanMerge{
    public:
        ScanMerge(sensor_msgs::PointCloud2 front_data,sensor_msgs::PointCloud2 back_data,float angle_incremenet,float time_increment,float scan_time,float range_min,float range_max,std::string frame_id,ros::Time stamp);
        sensor_msgs::LaserScan merge();

        float angle_min;
        float angle_max;
        float angle_increment;
        float time_increment;
        float scan_time;
        float range_min;
        float range_max;
        std::string frame_id;
        ros::Time stamp;

        sensor_msgs::PointCloud2 front_data;
        sensor_msgs::PointCloud2 back_data;

        sensor_msgs::LaserScan pointcloud_to_laserscan(Eigen::MatrixXf points);
};