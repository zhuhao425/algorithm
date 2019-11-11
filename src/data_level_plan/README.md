# 数据级融合方案
数据级融合的方案就是在收到多个激光雷达的数据后就将多个激光雷达的数据合起来，提供给其他模块。其他模块在使用该数据时，可以直接将该数据看成是一个激光雷达提供的。

## 方案分析
激光雷达要区分2D和3D，因为它们所提供的数据类型有所不同。3D激光雷达提供的数据类型是PointCloud，而PointCloud是存在拼接操作的，所以多个PointCloud可以先转换到同一个坐标系下，然后进行拼接，就可以完成任务。2D激光雷达就不一样了，它所提供的数据类型是LaserScan，而LaserScan没有拼接操作，需要先转换成PointCloud进行拼接，拼接完成后再按照LaserScan的数据特性还原成LaserScan。相对于3D激光雷达，2D激光雷达的数据级融合方案更加复杂。所以这里以2D激光雷达为例，实现数据级融合方案。
### LaserScan数据类型
具体的内容可以见 http://docs.ros.org/kinetic/api/sensor_msgs/html/msg/LaserScan.html 。LaserScan的数据是从angle_min到angle_max之间，每间隔一个angle_increment对应的点的距离，保存在ranges中。要想将多个LaserScan数据合并，可以按照这个思路，将对应的点的距离放置到对应的ranges[]中。
### 合并方法
虽然按照LaserScan数据的特性可以将多个LaserScan进行合并，但是该方法对雷达的安装位置要求很高，在实际应用时几乎不可能做到。而拼接点云的方式就相对要求较低，但是想更好的提升多个雷达的合并后的性能，雷达的安装位置很关键。这里的方案使用了turtlebot进行仿真测试，在bot上放置了两个hokuyo雷达，分别将雷达的数据发布在/scan_front和/scan_back中。合并模块在收到这两个雷达的数据后，首先会将LaserScan转换成PointCloud,然后根据对应的frame_id得到TF变换后对PointCloud进行变换得到类型为PointCloud2。最后将变换后的PointCloud2进行拼接。此时得到的PointCloud2对应着方案所需要的LaserScan，但是它们之间没有直接的对应关系。如果需要将PointCloud2转换到LaserScan，需要按照LaserScan数据的特性进行转换。从起始角度开始，将PointCloud2中的点对应到ranges[]中，详见ScanMerge。

## 使用方法
```bash
$> catkin_make
$> source devel/setup.bash
$> cd src/script
$> ./test_slam.sh
```
test_slam.sh是写好的脚本文件，运行该文件会挨个启动需要的节点。当节点全部启动后，可以使用键盘控制bot完成建图。在rviz中切换LaserScan的topic可以查看对应的雷达的数据,/scan是合并后的数据，/scan_front和/scan_back分别是前后两个雷达所提供的数据。

##总结
将多个雷达的数据进行合并的思路比较简单，但是实际的效果比较依赖雷达的安装位置。同时需要注意的是，多个雷达的数据合并后会导致数据量翻倍。而一般的SLAM算法会假设雷达一次扫描所提供的数据中点的数量有上限，比如gmapping中会假设点的数量不超过2048。如果LaserScan中的点超过了该上限，gmapping就会停止运行。所以必须要修改这个上限或者对数据进行将采样。
