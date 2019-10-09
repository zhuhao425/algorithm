#!/bin/sh
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_gazebo explore.launch" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch funsion_test test.launch" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"