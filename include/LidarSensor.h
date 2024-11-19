#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class LidarSensor : public Sensor {
public:
    LidarSensor(const string& model);
    string getType() const override;
    string getModel() const override;
    pair<int, int> getResponseRate() const override;
    vector<int> getOutputShape() const override;
    void simulateData() override;
};

#endif
