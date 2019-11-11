#!/bin/sh
xterm -e "source ../../devel/setup.bash; roslaunch myrobot turtlebot_world.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch rf2o_laser_odometry rf2o_laser_odometry.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch robot_pose_ekf robot_pose_ekf.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch;read"