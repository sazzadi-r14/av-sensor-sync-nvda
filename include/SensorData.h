#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <chrono>
#include <vector>
#include <variant>

// Variant to handle multiple data types (e.g., point clouds, position data, images)
using SensorOutput = std::variant<
    std::vector<std::vector<float>>, // For dynamic 2D arrays like Lidar, Radar
    std::vector<float>,              // For 1D arrays like GNSS velocity
    std::vector<std::vector<std::vector<int>>> // For Camera images (3D matrices)
>;

struct SensorData {
    int sensorId;                               // Unique ID for the sensor
    std::string sensorType;                    // Camera, Radar, etc.
    SensorOutput data;                         // Actual data from the sensor
    std::chrono::system_clock::time_point timestamp; // Timestamp of the reading
};

#endif
