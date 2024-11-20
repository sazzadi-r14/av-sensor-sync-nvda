![Brainstorm](brain_storm.jpg)

# AV Sensor Synchronization Simulation

This project simulates sensor synchronization in autonomous vehicles (AVs). It models multiple sensors—Camera, LiDAR, Radar, and GNSS—each with unique response times and data outputs. The goal is to achieve synchronized data collection, simulating how an AV would integrate sensor inputs to understand its environment comprehensively.

## Features

- **Sensor Simulation:** Each sensor type generates mock data representing real-world outputs.
- **Multithreading:** Sensors operate in parallel threads to mimic concurrent data generation.
- **Synchronization Management:** The SensorManager class handles data synchronization across different sensors.
- **Data Handling:** Utilizes a thread-safe ParallelQueue to manage sensor data efficiently.
- **Abstract Factory Pattern:** Implements the Abstract Factory design pattern via the SensorFactory class.
- **Extensibility:** Easily add new sensors or modify existing ones without altering the core system.
- **Profiling and Performance Metrics:** Profiles system performance, calculating optimal refresh rates and estimating data throughput.
- **JSON Serialization:** Saves sensor data to disk in JSON format using the [nlohmann/json](https://github.com/nlohmann/json) library. (This is very unstable, and needs further optimization.)


## Project Structure

```
av-sensor-sync-nvda/
├── include/
│   ├── CameraSensor.h
│   ├── GNSSSensor.h
│   ├── LidarSensor.h
│   ├── RadarSensor.h
│   ├── Sensor.h              # Abstract base class for sensors
│   ├── SensorData.h          # Defines SensorData structure
│   ├── SensorFactory.h       # Factory for creating sensor instances
│   ├── SensorManager.h       # Manages sensors and data synchronization
│   ├── ParallelQueue.h       # Thread-safe queue implementation
│   └── nlohmann/json.hpp     # JSON library for serialization
├── src/
│   ├── main.cpp              # Entry point of the program
│   ├── CameraSensor.cpp
│   ├── GNSSSensor.cpp
│   ├── LidarSensor.cpp
│   ├── RadarSensor.cpp
│   ├── Sensor.cpp
│   ├── SensorFactory.cpp
│   ├── SensorManager.cpp
│   └── ParallelQueue.cpp
├── CMakeLists.txt            # Configuration for CMake build system
├── README.md                 # Project description and setup instructions
└── ...                       # Additional files and directories
```

## Setup Instructions

### Prerequisites

- **C++ Compiler:** Modern C++ compiler supporting C++17 (e.g., `g++` 7.2 or higher).
- **CMake:** Version 3.10 or higher.
- **nlohmann/json Library:** Included in the include directory.

### Building and Running the Simulation

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd av-sensor-sync-nvda
   ```

2. **Create a Build Directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Run CMake**
   Generate the build configuration files:
   ```bash
   cmake ..
   ```

4. **Build the Project**
   Compile the source code:
   ```bash
   make
   ```

5. **Run the Simulation**
   Execute the compiled program:
   ```bash
   ./AVSensorSyncNVDA
   ```

## Detailed Overview

### Sensor Implementation

Each sensor simulates data generation specific to its real-world counterpart:

- **CameraSensor**
  - Simulates high-resolution image data.
  - Output Shape: `[2160, 3840, 3]` representing a 4K image with RGB channels.
  - Fixed response rate based on frames per second (FPS).

- **LidarSensor**
  - Generates 3D point cloud data.
  - Output Shape: `[88462, 4]` representing points with x, y, z coordinates and intensity.
  - Fixed response rate to mimic real-time scanning.

- **RadarSensor**
  - Produces detections including range, azimuth, velocity, and intensity.
  - Output Shape: Dynamic, based on the number of objects detected.
  - Variable response rate to simulate different refresh intervals.

- **GNSSSensor**
  - Provides positional data such as latitude, longitude, altitude, and velocities.
  - Output Shape: `[1, 11]` representing various navigation parameters.
  - Variable response rate to reflect sensor fusion scenarios.

### SensorManager Functionality

- **Start and Stop Operations:** Manages the lifecycle of sensor threads.
- **Data Processing Loop:** Performs data retrieval, synchronization, and dispatching in cycles.
- **System Profiling:** Calculates system refresh rate and throughput based on sensor characteristics.

### ParallelQueue Mechanics

- **Thread-Safe Operations:** Uses mutex locks to ensure safe concurrent access.
- **Latest Readings Retrieval:** Provides access to the most recent data from each sensor.
- **Data Clearing Mechanism:** Prevents unbounded growth by capping the queue size.

### Performance and Profiling

- **Refresh Rate Determination:** Based on the worst-case execution time (WCET) of sensors.
- **Throughput Estimation:** Calculates data handling capacity in bytes per second.
- **Profiling Output:** Displays sensor-specific performance metrics in a formatted manner.

## Extending the Project

### Adding New Sensors

1. **Create a New Sensor Class**
   - Derive from the abstract Sensor class.
   - Implement all virtual functions, including data generation and response rates.

2. **Update SensorFactory**
   - Modify SensorFactory.cpp and SensorFactory.h

 to include the new sensor type.
   - Ensure the factory can instantiate the new sensor based on string identifiers.

3. **Modify Main Program**
   - Update main.cpp to create instances of the new sensor.
   - Register the sensor with SensorManager for inclusion in the simulation.



### Notes

Assumptions in the system
based on https://developer.nvidia.com/drive/ecosystem-orin
add atleast one of all kind of supported sensors.
Lidar, Radar, GNSS, Camera




one thing you wanna think about that tsensors might percieve differetn thing by the time input from another sensor ocmes in, you have to make a design decision of what's the right thing to do under this situation. do you take average, or something else, or do you just take the earliest possible response or something like that.



Trying to replicate the Mercedes x Nvidia System

Cool ideas from nvidia driveworks sdk
- synchronzied timestamping of sensor data. look at cool ways to create a data structure, think about the insertion time of the DSA as this is very performance critical. also this is another thing that should be part of the profiling, as eventually you may wanna look how much time insertion took, and delta of average polling rate from all sensors.
- replaying this would be cool haha
- 