#ifndef RADAR_SENSOR_H
#define RADAR_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

#include "ParallelQueue.h"
#include <vector>

class RadarSensor : public Sensor {
public:
    RadarSensor(const std::string& model);

    std::string getType() const override;
    std::string getModel() const override;
    std::pair<int, int> getResponseRate() const override;
    std::vector<int> getOutputShape() const override;
    void simulateData(ParallelQueue& queue, int sensorId) override;

private:
    int randomObjectCount() const;
};

#endif
