#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include "sensor_msgs/LaserScan.h"
#include <pcl/common/transforms.h>

ScanMerge::ScanMerge(sensor_msgs::PointCloud2 front_data,sensor_msgs::PointCloud2 back_data,float angle_increment,float time_increment,float scan_time,float range_min,float range_max,std::string frame_id,ros::Time stamp)
{
    this->front_data = front_data;
    this->back_data = back_data;
    this->angle_min = -M_PI;
    this->angle_max = M_PI;
    this->angle_increment = angle_increment;
    this->time_increment = time_increment;
    this->scan_time = scan_time;
    this->range_min = range_min;
    this->range_max = range_max;
    this->frame_id = frame_id;
    this->stamp = stamp;
    //ROS_INFO("scanmerge :     %f  %f",angle_increment,time_increment);
}

sensor_msgs::LaserScan ScanMerge::merge()
{
    pcl::PCLPointCloud2 front_data_pcl,back_data_pcl,merged_cloud;
    pcl_conversions::toPCL(front_data, front_data_pcl);
    pcl_conversions::toPCL(back_data, back_data_pcl);
   // ROS_INFO("conversions complete,get PCLPointCloud2");
    
    pcl::concatenatePointCloud(front_data_pcl, back_data_pcl, merged_cloud);
    //ROS_INFO("concatenate complete,into one cloud");
    Eigen::MatrixXf points;//表示任意大小的元素类型为float型的矩阵变量，其大小只有在运行时被赋值之后才能知道。
    getPointCloudAsEigen(merged_cloud,points);//得到merged_cloud主题将points按照矩阵的特征向量形式输出。
    //ROS_INFO("conver to laserscan");
    return pointcloud_to_laserscan(points);
}

sensor_msgs::LaserScan ScanMerge::pointcloud_to_laserscan(Eigen::MatrixXf points)
{
    //将结合的merged_cloud转换成output，并将output发布出去。这个函数是通过括号里的这些参数来实现函数名这个功能
    sensor_msgs::LaserScan output;//新输出一个output名称的scan对象指针
    //output->header = pcl_conversions::fromPCL(merged_cloud->header);//pcl转换
    output.header.frame_id = "/base_footprint";
    output.header.stamp = this->stamp;  //fixes #265
    output.angle_min = this->angle_min;
    output.angle_max = this->angle_max;
    output.angle_increment = this->angle_increment;
    output.time_increment = this->time_increment;
    output.scan_time = this->scan_time;
    output.range_min = this->range_min;
    output.range_max = this->range_max;

   // ROS_INFO("output:   %f %f",output.angle_increment,output.time_increment);
    //ROS_INFO("angle_min:%f angle_max:%f angle_increment:%f time_increment:%f range_min:%f range_max:%f",output.angle_min,output.angle_max,output.angle_increment,output.time_increment,output.range_min,output.range_max);

    uint32_t ranges_size = std::ceil((output.angle_max - output.angle_min) / output.angle_increment);//计算出扫描的个数有多少个
    output.ranges.assign(ranges_size, output.range_max + 1.0);//ranges就是激光雷达扫描的点。它的范围是比range_max范围内的点还多一米的范围。

    //ROS_INFO("laserscan's info registered");
    for(int i=0; i<points.cols(); i++)//矩阵的列数
    {
        const float &x = points(0,i);
        const float &y = points(1,i);
        const float &z = points(2,i);//一共三行i列


        if ( std::isnan(x) || std::isnan(y) || std::isnan(z) )//如果含有非零值则对，如果是0则错。就是有0的点都排除
        {
            ROS_DEBUG("rejected for nan in point(%f, %f, %f)\n", x, y, z);
            continue;
        }


        double range_sq = y*y+x*x;
        double range_min_sq_ = output.range_min * output.range_min;
        if (range_sq < range_min_sq_) {
            ROS_DEBUG("rejected for range %f below minimum value %f. Point: (%f, %f, %f)", range_sq, range_min_sq_, x, y, z);
            continue;//拒绝小于范围的点，都排除
        }


        double angle = atan2(y, x);
        if (angle < output.angle_min || angle > output.angle_max)
        {
            ROS_DEBUG("rejected for angle %f not in range (%f, %f)\n", angle, output.angle_min, output.angle_max);
            continue;//不在范围内的点全排除
        }
        int index = (angle - output.angle_min) / output.angle_increment;//点的索引

        if (output.ranges[index] * output.ranges[index] > range_sq)
            output.ranges[index] = sqrt(range_sq);
    }

    //ROS_INFO("insert complete");
    return output;//将output发布出去
}
