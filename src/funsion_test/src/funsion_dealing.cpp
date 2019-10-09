#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

ros::Publisher scan_funsion_pub;
ros::Subscriber scan_front_sub;
ros::Subscriber scan_back_sub;

sensor_msgs::LaserScan front_data;
sensor_msgs::LaserScan back_data;
bool front=false;
bool back=false;

void funsion_data()
{
    front = false;
    back = false;
    sensor_msgs::LaserScan data;
    ros::Time scan_time = ros::Time::now();
    data.header.frame_id = front_data.header.frame_id;
    data.header.stamp = scan_time;
    data.angle_min = front_data.angle_min;
    data.angle_max = front_data.angle_max;
    data.angle_increment = front_data.angle_increment;
    data.time_increment = front_data.time_increment;
    data.range_min = front_data.range_min;
    data.range_max = front_data.range_max + back_data.range_max;

    data.ranges.resize(data.range_max);
    data.intensities.resize(data.range_max);

    for(auto i = front_data.range_max;i<data.range_max;i++)
    {
        data.ranges[i] = back_data.ranges[i - front_data.range_max];
        data.intensities[i] = back_data.intensities[i - front_data.range_max];
    }
    scan_funsion_pub.publish(data);
}

void scanFrontCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    front_data = *msgs;
    front = true;
    if(front && back)
        funsion_data();
}

void scanBackCallback(const sensor_msgs::LaserScan::ConstPtr& msgs)
{
    back_data = *msgs;
    back = true;
    if(front && back)
        funsion_data();
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "funsion_dealing");
  ros::NodeHandle n;
  scan_front_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_front",5,scanFrontCallback);
  scan_back_sub = n.subscribe<sensor_msgs::LaserScan>("/scan_back",5,scanBackCallback);
  scan_funsion_pub = n.advertise<sensor_msgs::LaserScan>("/scan", 5);

  ros::spin();
}