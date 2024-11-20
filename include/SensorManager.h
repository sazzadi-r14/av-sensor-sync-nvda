#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Sensor.h"
#include "ParallelQueue.h"
#include <vector>
#include <thread>
#include <memory>
#include <fstream> // For file handling

class SensorManager {
public:
    void addSensor(std::shared_ptr<Sensor> sensor, int sensorId);
    void profileSystem();
    void start();
    void stop();

private:
    std::vector<std::pair<std::shared_ptr<Sensor>, int>> sensors; // Sensors with IDs
    ParallelQueue dataQueue;
    bool running = true;
    int refreshRate = 1000; // Refresh rate in milliseconds (default)

    void processData();
    void saveDataToDisk(const std::vector<SensorData>& data);
    void sendToControlSystem(const std::unordered_map<int, SensorData>& latestData);
    int calculateRefreshRate();
};

#endif