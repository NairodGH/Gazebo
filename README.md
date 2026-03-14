# <p align="center">🤖 Gazebo 🚗</p>

<p align="center">
    <!-- <img src="Gazebo.gif"> -->
</p>

## 🔍 About

Gazebo is a personal discovery project on the [open-source 3D robotics simulator](https://en.wikipedia.org/wiki/Gazebo_(simulator)) of the same name and its [ROS2](https://en.wikipedia.org/wiki/Robot_Operating_System) binding. It builds off their [tutorial](https://gazebosim.org/docs/latest/tutorials/) of a lidar car, the goal being to develop the cpp [lidar](https://fr.wikipedia.org/wiki/Lidar) [SLAM](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping) node.

## 💻 Requirements

Tested on Windows 11 WSL2 Ubuntu 24.04 (recommend it).\
You will need:
- [Gazebo Harmonic](https://gazebosim.org/docs/harmonic/install/) and the ROS pairing (follow the install page)
- [ROS 2 Jazzy](https://docs.ros.org/en/jazzy/Installation.html)
- [Cmake](https://cmake.org/download/)
- [Colcon](https://colcon.readthedocs.io/en/released/)
- `sudo apt install libgz-transport13-dev libgz-msgs10-dev`

## 🔧 Building

```bash
git clone https://github.com/NairodGH/Gazebo.git
cd Gazebo
colcon build --packages-select avoid_wall
cd src/avoid_wall && mkdir -p build && cd build
cmake .. && make -j$(nproc)
cd ../../..
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
echo "source $(pwd)/install/avoid_wall/share/avoid_wall/local_setup.bash" >> ~/.bashrc
source ~/.bashrc
```

## 🚀 Running

If you use VSCode, `.vscode/tasks.json` is included with preconfigured tasks (VSCode must be opened from a terminal for the ROS environment to be available).\
Open the repo in VSCode from a terminal (`code .`) then use `Ctrl+Shift+P` -> `Tasks: Run Task`:
- `build and launch (ros2)` builds with colcon and launches Gazebo + bridge + ROS 2 node
- `build and launch (gz)` builds with cmake and launches Gazebo + standalone Gazebo node

Or, manually for the ROS 2 version:
```bash
ros2 launch avoid_wall my_launch.py
```

and for the Gazebo version :
```bash
gz sim src/avoid_wall/worlds/building_robot.sdf &
sleep 3 && src/avoid_wall/build/lidar_node_gz
```

## 🎮 Usage

No matter which version, the Gazebo simulator will open and all you have to do is start the simulation by clicking the bottom left play button.\
Once the simulation is started, you may control the car with directional keys (on Gazebo version, turn on the Key Publisher plugin by searching and clicking it from the top right ellipsis).

## 🤝 Author

[Nairod](https://github.com/NairodGH)