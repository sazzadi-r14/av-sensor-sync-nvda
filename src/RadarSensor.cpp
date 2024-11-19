#include "RadarSensor.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>

RadarSensor::RadarSensor(const std::string& model) {
    this->type = "Radar";
    this->model = model;
    this->responseRate = {20, 50}; // Random delay between 20ms to 50ms
    this->outputShape = {0, 4};   // Dynamic: n objects with {range, azimuth, velocity, intensity}
}

std::string RadarSensor::getType() const {
    return type;
}

std::string RadarSensor::getModel() const {
    return model;
}

std::pair<int, int> RadarSensor::getResponseRate() const {
    return responseRate;
}

std::vector<int> RadarSensor::getOutputShape() const {
    return {randomObjectCount(), 4};
}

void RadarSensor::simulateData(ParallelQueue& queue, int sensorId) {
    while (true) {
        int delay = rand() % (responseRate.second - responseRate.first + 1) + responseRate.first;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        int objectCount = randomObjectCount();
        std::vector<std::vector<float>> detections;
        for (int i = 0; i < objectCount; ++i) {
            detections.push_back({static_cast<float>(rand() % 500), static_cast<float>(rand() % 360), static_cast<float>(rand() % 20 - 10), static_cast<float>(rand() % 100) / 100.0f});
        }

        SensorData sensorData{
            sensorId,
            "Radar",
            detections,
            std::chrono::system_clock::now()
        };

        queue.push(sensorData);
        std::cout << "Radar (" << model << ") pushed detection data for " << objectCount << " objects.\n";
    }
}

int RadarSensor::randomObjectCount() const {
    return rand() % 50 + 1; // Between 1 and 50 objects
}
