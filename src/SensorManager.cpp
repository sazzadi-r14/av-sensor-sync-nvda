#include "SensorManager.h"
#include <iostream>

void SensorManager::addSensor(std::shared_ptr<Sensor> sensor, int sensorId) {
    sensors.emplace_back(sensor, sensorId);
}

void SensorManager::start() {
    // Launch threads for each sensor
    for (const auto& [sensor, id] : sensors) {
        threads.emplace_back(&Sensor::simulateData, sensor, std::ref(dataQueue), id);
    }

    // Launch processing thread
    threads.emplace_back(&SensorManager::processData, this);
}

void SensorManager::stop() {
    running = false;

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void SensorManager::processData() {
    while (running) {
        // Wait for new data from the queue
        SensorData data = dataQueue.waitAndPop();

        // Process the data (e.g., sync timestamps, log to storage)
        std::cout << "Processing data from Sensor ID: " << data.sensorId
                  << ", Type: " << data.sensorType << ", Timestamp: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         data.timestamp.time_since_epoch())
                         .count()
                  << " ms\n";
    }
}
