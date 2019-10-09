#include <ros/ros.h>
#include <string.h>
#include <tf/transform_listener.h>
#include <pcl_ros/transforms.h>
#include <laser_geometry/laser_geometry.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include "sensor_msgs/LaserScan.h"
#include "pcl_ros/point_cloud.h"
#include <Eigen/Dense>
#include <dynamic_reconfigure/server.h>
#include <ira_laser_tools/laserscan_multi_mergerConfig.h>


using namespace std;
//using namespace pcl;
using namespace laserscan_multi_merger;


class LaserscanMerger
{
public:
    LaserscanMerger();
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan, std::string topic);
    void scan_to_mergedscan(const sensor_msgs::LaserScan::ConstPtr& scan);
    void reconfigureCallback(laserscan_multi_mergerConfig &config, uint32_t level);


private:
    ros::NodeHandle node_;
    
    tf::TransformListener tfListener_;


    
    ros::Publisher laser_scan_publisher_;
    vector<ros::Subscriber> scan_subscribers;

    vector<string> input_topics;

    void laserscan_topic_parser();


    double angle_min;
    double angle_max;
    double angle_increment;
    double time_increment;
    double scan_time;
    double range_min;
    double range_max;


    string destination_frame;
    string scan_destination_topic;
    string laserscan_topics;
};
//
//
void LaserscanMerger::reconfigureCallback(laserscan_multi_mergerConfig &config, uint32_t level)
{
    this->angle_min = config.angle_min;
    this->angle_max = config.angle_max;
    this->angle_increment = config.angle_increment;
    this->time_increment = config.time_increment;
    this->scan_time = config.scan_time;
    this->range_min = config.range_min;
    this->range_max = config.range_max;
}


void LaserscanMerger::laserscan_topic_parser()
{
// LaserScan topics to subscribe
    ros::master::V_TopicInfo topics;
    ros::master::getTopics(topics);


    istringstream iss(laserscan_topics);//获取两个激光雷达的topic
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));


    vector<string> tmp_input_topics;


    for(int i=0;i<tokens.size();++i)//i代表laserscan_topics 的个数 
    {
        for(int j=0;j<topics.size();++j)//j代表所有topics的个数
        {
            if( (tokens[i].compare(topics[j].name) == 0) && (topics[j].datatype.compare("sensor_msgs/LaserScan") == 0) )
            {
                tmp_input_topics.push_back(topics[j].name);
            }
        }
    }//从所有topic里选出两个激光雷达的topic并赋给tmp_input_topics


    sort(tmp_input_topics.begin(),tmp_input_topics.end());//按大小调整一下顺序；
    std::vector<string>::iterator last = std::unique(tmp_input_topics.begin(), tmp_input_topics.end());//去掉重复的；比如有两个topic同名就去掉一个
    tmp_input_topics.erase(last, tmp_input_topics.end());




    // Do not re-subscribe if the topics are the same
    if( (tmp_input_topics.size() != input_topics.size()) || !equal(tmp_input_topics.begin(),tmp_input_topics.end(),input_topics.begin()))
    {


        // Unsubscribe from previous topics
        for(int i=0; i<scan_subscribers.size(); ++i)//如果是if这种情况，则先不从当前的主题订阅，即先把scan_subscriber关闭。
        scan_subscribers[i].shutdown();//即不订阅。


        input_topics = tmp_input_topics;//再将tmp这个赋给input这个。此时的input就是laserscan_topics的两个topic了
        if(input_topics.size() > 0)
        {
            scan_subscribers.resize(input_topics.size());
            //clouds_modified.resize(input_topics.size());
            //clouds.resize(input_topics.size());
            ROS_INFO("Subscribing to topics\t%ld", scan_subscribers.size());//将这些主题全都改成这两个。
            cout <<"Subscribing to topics:"<<' ';
            for(int i=0; i<input_topics.size(); ++i)
            {
                scan_subscribers[i] = node_.subscribe<sensor_msgs::LaserScan> (input_topics[i].c_str(), 1, boost::bind(&LaserscanMerger::scanCallback,this, _1, input_topics[i]));//这个是将订阅的主题显示出来。
                //clouds_modified[i] = false;
                cout<< input_topics[i] << " ";
            }
        }//scan_subscriber订阅input_topics的两个主题
        else
            ROS_INFO("Not subscribed to any topic.");
    }
}


LaserscanMerger::LaserscanMerger()
{
    ros::NodeHandle nh("~");//这是构造函数，实例化对象的时候首先执行构造函数，第一步


    nh.getParam("destination_frame", destination_frame);
    //nh.getParam("cloud_destination_topic", cloud_destination_topic);
    nh.getParam("scan_destination_topic", scan_destination_topic);
    nh.getParam("laserscan_topics", laserscan_topics);


    this->laserscan_topic_parser();//第二步


    //point_cloud_publisher_ = node_.advertise<sensor_msgs::PointCloud2> (cloud_destination_topic.c_str(), 1, false);//发布/merged_cloud
    laser_scan_publisher_ = node_.advertise<sensor_msgs::LaserScan> (scan_destination_topic.c_str(), 1, false);//发布scan_destination_topic 即/scan也是新output


    tfListener_.setExtrapolationLimit(ros::Duration(0.1));//???????????????
}


void LaserscanMerger::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan, std::string topic)//参数是scan 和 topic
{
    sensor_msgs::PointCloud tmpCloud1,tmpCloud2;
    sensor_msgs::PointCloud2 tmpCloud3;


    // Verify that TF knows how to transform from the received scan to the destination scan frame
    tfListener_.waitForTransform(scan->header.frame_id.c_str(), destination_frame.c_str(), scan->header.stamp, ros::Duration(1));


    projector_.transformLaserScanToPointCloud(scan->header.frame_id, *scan, tmpCloud1, tfListener_);//将激光雷达转换成点云
    try
    {
        tfListener_.transformPointCloud(destination_frame.c_str(), tmpCloud1, tmpCloud2);//将激光雷达转换成的点云tmpCloud1通过tf转换到merge_link并发布为tmpCloud2
    }catch (tf::TransformException ex)
    {
        ROS_ERROR("%s",ex.what());
        return;
    }


    for(int i=0; i<input_topics.size(); ++i)
    {
        if(topic.compare(input_topics[i]) == 0)
        {
            sensor_msgs::convertPointCloudToPointCloud2(tmpCloud2,tmpCloud3);//将PointCloud类型的tmpCloud2转换成PointCloud2类型的tmpCloud3
            pcl_conversions::toPCL(tmpCloud3, clouds[i]);
            clouds_modified[i] = true;
        }
    }


    // Count how many scans we have
    int totalClouds = 0;
    for(int i=0; i<clouds_modified.size(); ++i)
    if(clouds_modified[i])
        ++totalClouds;


    // Go ahead only if all subscribed scans have arrived
    if(totalClouds == clouds_modified.size())
    {
        pcl::PCLPointCloud2 merged_cloud = clouds[0];
        clouds_modified[0] = false;


        for(int i=1; i<clouds_modified.size(); ++i)
        {
            pcl::concatenatePointCloud(merged_cloud, clouds[i], merged_cloud);
            clouds_modified[i] = false;
        }


        point_cloud_publisher_.publish(merged_cloud);//发布merged_cloud主题


        Eigen::MatrixXf points;//表示任意大小的元素类型为float型的矩阵变量，其大小只有在运行时被赋值之后才能知道。
        getPointCloudAsEigen(merged_cloud,points);//得到merged_cloud主题将points按照矩阵的特征向量形式输出。


        pointcloud_to_laserscan(points, &merged_cloud, scan);//这里调用的是下面这个函数
    }//input是cloud2类型的output是scan，上面这三个就把point_cloud输出成laserscan了。
}


void LaserscanMerger::scan_to_mergedscan(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    //将结合的merged_cloud转换成output，并将output发布出去。这个函数是通过括号里的这些参数来实现函数名这个功能
    sensor_msgs::LaserScanPtr output(new sensor_msgs::LaserScan());//新输出一个output名称的scan对象指针
    //output->header = pcl_conversions::fromPCL(merged_cloud->header);//pcl转换
    output->header.frame_id = destination_frame.c_str();
    output->header.stamp = scan->header.stamp;  //fixes #265
    output->angle_min = this->angle_min;
    output->angle_max = this->angle_max;
    output->angle_increment = this->angle_increment;
    output->time_increment = this->time_increment;
    output->scan_time = this->scan_time;
    output->range_min = this->range_min;
    output->range_max = this->range_max;


    uint32_t ranges_size = std::ceil((output->angle_max - output->angle_min) / output->angle_increment);//计算出扫描的个数有多少个
    output->ranges.assign(ranges_size, output->range_max + 1.0);//ranges就是激光雷达扫描的点。它的范围是比range_max范围内的点还多一米的范围。


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
        double range_min_sq_ = output->range_min * output->range_min;
        if (range_sq < range_min_sq_) 
        {
            ROS_DEBUG("rejected for range %f below minimum value %f. Point: (%f, %f, %f)", range_sq, range_min_sq_, x, y, z);
            continue;//拒绝小于范围的点，都排除
        }


        double angle = atan2(y, x);
        if (angle < output->angle_min || angle > output->angle_max)
        {
            ROS_DEBUG("rejected for angle %f not in range (%f, %f)\n", angle, output->angle_min, output->angle_max);
            continue;//不在范围内的点全排除
        }
        int index = (angle - output->angle_min) / output->angle_increment;//点的索引




        if (output->ranges[index] * output->ranges[index] > range_sq)
            output->ranges[index] = sqrt(range_sq);
    }


    laser_scan_publisher_.publish(output);//将output发布出去
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "laser_multi_merger");


    LaserscanMerger _laser_merger;


    dynamic_reconfigure::Server<laserscan_multi_mergerConfig> server;
    dynamic_reconfigure::Server<laserscan_multi_mergerConfig>::CallbackType f;


    f = boost::bind(&LaserscanMerger::reconfigureCallback,&_laser_merger, _1, _2);
    server.setCallback(f);


    ros::spin();


    return 0;
}//也就是说整个程序是先按点云形式结合，然后再将点云转化成scan