#include "SensorManager.h"

using namespace std;

void SensorManager::addSensor(unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void SensorManager::start() {
    for (auto& sensor : sensors) {
        sensorThreads.emplace_back(&Sensor::simulateData, sensor.get());
    }

    for (auto& thread : sensorThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
