#include "SensorManager.h"
#include <iostream>

void SensorManager::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
}

void SensorManager::collectData() {
    for (const auto& sensor : sensors) {
        std::cout << sensor->generateData() << std::endl;
    }
}
