#include "SensorManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip> // For formatting
#include <cmath>
#include <nlohmann/json.hpp> // For JSON serialization

using json = nlohmann::json;

void SensorManager::addSensor(std::shared_ptr<Sensor> sensor, int sensorId) {
    sensors.emplace_back(sensor, sensorId);
}

void SensorManager::profileSystem() {
    std::cout << "=== SYSTEM PROFILING ===\n";
    std::cout << std::setw(15) << "Sensor ID"
              << std::setw(15) << "Type"
              << std::setw(20) << "Best Time (ms)"
              << std::setw(20) << "Worst Time (ms)"
              << std::setw(25) << "Best Polling Rate (Hz)"
              << std::setw(20) << "Data Shape"
              << std::setw(30) << "Estimated Throughput (B/s)\n";
    std::cout << std::string(130, '=') << "\n";

    int maxWorstCaseTime = 0;

    size_t total_throughput = 0;

    for (const auto& [sensor, id] : sensors) {
        auto [best, worst] = sensor->getResponseRate();
        maxWorstCaseTime = std::max(maxWorstCaseTime, worst);

        // Compute best polling rate
        double bestPollingRate = best > 0 ? 1000.0 / best : 0.0;

        // Data shape and throughput
        auto dataShape = sensor->getOutputShape();
        size_t dataSize = 1;
        for (int dim : dataShape) {
            dataSize *= dim; // Compute total number of elements
        }

        // Estimate data type size
        size_t typeSize = 0;
        if (std::holds_alternative<std::vector<std::vector<float>>>(sensor->getOutputShapeVariant())) {
            typeSize = sizeof(float);
        } else if (std::holds_alternative<std::vector<std::vector<std::vector<int>>>>(sensor->getOutputShapeVariant())) {
            typeSize = sizeof(int);
        } else if (std::holds_alternative<std::vector<float>>(sensor->getOutputShapeVariant())) {
            typeSize = sizeof(float);
        }

        size_t throughput = static_cast<size_t>((dataSize * typeSize * bestPollingRate));
        total_throughput += throughput;

        // Print profiling info
        std::cout << std::setw(15) << id
                  << std::setw(15) << sensor->getType()
                  << std::setw(20) << best
                  << std::setw(20) << worst
                  << std::setw(25) << std::fixed << std::setprecision(2) << bestPollingRate
                  << std::setw(20) << "[" << dataShape[0];
        for (size_t i = 1; i < dataShape.size(); ++i) {
            std::cout << "x" << dataShape[i];
        }
        std::cout << "]"
                  << std::setw(30) << throughput << "\n";
    }
    
    std::cout << std::string(130, '=') << "\n";

    std::cout << "Total Estimated Throughput: " << (total_throughput) / (1024 * 1024) << " MB/s\n";

    refreshRate = maxWorstCaseTime; // WCET as the system refresh rate

    std::cout << "\nSystem Refresh Rate (WCET): " << refreshRate << " ms\n";
    std::cout << "Press ENTER to confirm and start the system...\n";

    std::cin.get(); // Wait for user confirmation
}




void SensorManager::start() {
    // Profile the system before starting
    profileSystem();

    // Launch threads for each sensor
    std::vector<std::thread> sensorThreads;
    for (const auto& [sensor, id] : sensors) {
        sensorThreads.emplace_back(&Sensor::simulateData, sensor, std::ref(dataQueue), id);
    }
    std::cout << "All sensors started." << std::endl;

    // Start processing thread
    std::thread processingThread(&SensorManager::processData, this);

    // Join sensor threads
    for (auto& thread : sensorThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Join processing thread
    if (processingThread.joinable()) {
        processingThread.join();
    }
}

void SensorManager::stop() {
    running = false;
}

void SensorManager::processData() {
    while (running) {
        auto startTime = std::chrono::steady_clock::now();

        // Retrieve the latest sensor data
        auto latestData = dataQueue.retrieveLatest();

        // Retrieve all historical data and clear the queue
        auto allData = dataQueue.retrieveAllAndClear();

        // Save historical data to disk
        saveDataToDisk(allData);

        // Send the latest data to the control system
        sendToControlSystem(latestData);

        // Wait for the remaining time in the refresh cycle
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        if (elapsedMs < refreshRate) {
            std::this_thread::sleep_for(std::chrono::milliseconds(refreshRate - elapsedMs));
        }
    }
}

void SensorManager::saveDataToDisk(const std::vector<SensorData>& data) {
    json jsonData;

    for (const auto& sensorData : data) {
        json entry;
        entry["sensorId"] = sensorData.sensorId;
        entry["sensorType"] = sensorData.sensorType;
        entry["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 sensorData.timestamp.time_since_epoch())
                                 .count();

        // Serialize data based on its type
        if (std::holds_alternative<std::vector<std::vector<float>>>(sensorData.data)) {
            entry["data"] = std::get<std::vector<std::vector<float>>>(sensorData.data);
        } else if (std::holds_alternative<std::vector<float>>(sensorData.data)) {
            entry["data"] = std::get<std::vector<float>>(sensorData.data);
        } else if (std::holds_alternative<std::vector<std::vector<std::vector<int>>>>(sensorData.data)) {
            entry["data"] = std::get<std::vector<std::vector<std::vector<int>>>>(sensorData.data);
        }

        jsonData.push_back(entry);
    }

    // Write to disk
    std::ofstream outFile("sensor_data.json", std::ios::app);
    outFile << jsonData.dump(4) << std::endl;
}

void SensorManager::sendToControlSystem(const std::unordered_map<int, SensorData>& latestData) {
    for (const auto& [id, sensorData] : latestData) {
        // Simulate sending to the control system
        std::cout << "Sending data to control system: Sensor ID " << id
                  << ", Type: " << sensorData.sensorType << std::endl;
    }
}

int SensorManager::calculateRefreshRate() {
    int maxTime = 0;

    for (const auto& [sensor, _] : sensors) {
        auto [best, worst] = sensor->getResponseRate();
        maxTime = std::max(maxTime, worst);
    }

    return maxTime;
}
