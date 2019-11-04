#!/bin/sh
xterm -e "export TURTLEBOT_GAZEBO_WORLD_FILE=/home/zh/workspace/multi_lidar_scan/src/worlds/playground.world; source ../../devel/setup.bash; roslaunch myrobot turtlebot_world.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch data_level_plan data_level_plan.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch myrobot gmapping_demo.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch myrobot view_navigation.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"