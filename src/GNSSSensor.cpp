#include "GNSSSensor.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>

GNSSSensor::GNSSSensor(const std::string& model) {
    this->type = "GNSS";
    this->model = model;
    this->responseRate = {10, 50}; // 10ms to 50ms (IMU + GNSS fusion rate)
    this->outputShape = {1, 11};   // Latitude, Longitude, Altitude, Speed, Velocity, ax, ay, az, wx, wy, wz
}

std::string GNSSSensor::getType() const {
    return type;
}

std::string GNSSSensor::getModel() const {
    return model;
}

std::pair<int, int> GNSSSensor::getResponseRate() const {
    return responseRate;
}

std::vector<int> GNSSSensor::getOutputShape() const {
    return outputShape;
}

void GNSSSensor::simulateData(ParallelQueue& queue, int sensorId) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(responseRate.first));

        // Generate the 1x11 GNSS data vector
        std::vector<float> gnssData = generateGNSSData();

        SensorData sensorData{
            sensorId,
            "GNSS",
            gnssData,
            std::chrono::system_clock::now()
        };

        queue.push(sensorData);

        // Log GNSS simulation
        std::cout << "GNSS (" << model << ") pushed 1x11 data: ";
        for (const auto& val : gnssData) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<float> GNSSSensor::generateGNSSData() const {
    // Generate mock data for GNSS
    std::vector<float> data(11);

    // Mock values for position, speed, acceleration, and angular velocity
    data[0] = 37.7749 + static_cast<float>(rand() % 100) / 1000.0;  // Latitude
    data[1] = -122.4194 + static_cast<float>(rand() % 100) / 1000.0; // Longitude
    data[2] = static_cast<float>(rand() % 100);                     // Altitude
    data[3] = static_cast<float>(rand() % 30 + 1);                  // Speed
    data[4] = static_cast<float>(rand() % 360);                     // Direction
    data[5] = static_cast<float>(rand() % 10 - 5);                  // ax
    data[6] = static_cast<float>(rand() % 10 - 5);                  // ay
    data[7] = 9.81f;                                                // az (gravity)
    data[8] = static_cast<float>(rand() % 100) / 100.0;             // wx
    data[9] = static_cast<float>(rand() % 100) / 100.0;             // wy
    data[10] = static_cast<float>(rand() % 100) / 100.0;            // wz

    return data;
}
