#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#include "ParallelQueue.h"
#include <vector>

class LidarSensor : public Sensor {
public:
    LidarSensor(const std::string& model);

    std::string getType() const override;
    std::string getModel() const override;
    std::pair<int, int> getResponseRate() const override;
    std::vector<int> getOutputShape() const override;
     // Return the variant-based data representation
    SensorOutput getOutputShapeVariant() const override;
    void simulateData(ParallelQueue& queue, int sensorId) override;

private:
    int n; // Number of points (dynamic in future models, fixed at 88462 here)
};

#endif
