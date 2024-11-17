#include <iostream>
#include "Sensor.h"
#include "SensorManager.h"

// Include the specific sensor implementation
#include "Sensor.cpp"

int main() {
    SensorManager manager;

    // Create a Lidar sensor and add it to the manager
    Sensor* lidar = new LidarSensor();
    manager.addSensor(lidar);

    // Collect data
    manager.collectData();

    delete lidar; // Clean up dynamically allocated memory
    return 0;
}
