cmake_minimum_required(VERSION 3.10)
project(AVSensorSyncNVDA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add source files
add_executable(AVSensorSyncNVDA src/main.cpp src/SensorManager.cpp src/SensorFactory.cpp src/LidarSensor.cpp src/RadarSensor.cpp src/CameraSensor.cpp src/GNSSSensor.cpp src/ParallelQueue.cpp)
