#!/bin/sh
xterm -e "source ../../devel/setup.bash; roslaunch myrobot turtlebot_world.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch amcl amcl_demo.launch;read" &
sleep 5
xterm -e "source ../../devel/setup.bash; roslaunch myrobot view_navigation.launch;read"