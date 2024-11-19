#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Sensor.h"
#include "ParallelQueue.h"
#include <vector>
#include <thread>
#include <memory>

class SensorManager {
public:
    void addSensor(std::shared_ptr<Sensor> sensor, int sensorId);
    void start();
    void stop();

private:
    std::vector<std::pair<std::shared_ptr<Sensor>, int>> sensors; // Sensors with IDs
    std::vector<std::thread> threads;
    ParallelQueue dataQueue;
    bool running = true;

    void processData(); // Handle data synchronization and forwarding
};

#endif
