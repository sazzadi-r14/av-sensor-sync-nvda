#include "LidarSensor.h"
#include <chrono>
#include <thread>
#include <iostream>

LidarSensor::LidarSensor(const std::string& model) {
    this->type = "Lidar";
    this->model = model;
    this->responseRate = {50, 50}; // Fixed at 20 Hz
    this->outputShape = {88462, 4}; // 4 = x, y, z, intensity
    this->n = 88462;
}

std::string LidarSensor::getType() const {
    return type;
}

std::string LidarSensor::getModel() const {
    return model;
}

std::pair<int, int> LidarSensor::getResponseRate() const {
    return responseRate;
}

std::vector<int> LidarSensor::getOutputShape() const {
    return outputShape;
}

SensorOutput LidarSensor::getOutputShapeVariant() const {
    return std::vector<std::vector<float>>(
        n, std::vector<float>{0.0f, 0.0f, 0.0f, 0.0f}); // x, y, z, intensity
}

void LidarSensor::simulateData(ParallelQueue& queue, int sensorId) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(responseRate.first));

        // Simulate point cloud data
        std::vector<std::vector<float>> pointCloud;
        for (int i = 0; i < n; ++i) {
            pointCloud.push_back({static_cast<float>(rand() % 100), static_cast<float>(rand() % 100), static_cast<float>(rand() % 100), static_cast<float>(static_cast<float>(rand() % 10) / 10.0f)});
        }

        SensorData sensorData{
            sensorId,
            "Lidar",
            pointCloud,
            std::chrono::system_clock::now()
        };

        queue.push(sensorData);
        //std::cout << "Lidar (" << model << ") pushed point cloud data.\n";
    }
}
