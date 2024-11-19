#ifndef RADAR_SENSOR_H
#define RADAR_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

class RadarSensor : public Sensor {
public:
    RadarSensor(const string& model);
    string getType() const override;
    string getModel() const override;
    pair<int, int> getResponseRate() const override;
    vector<int> getOutputShape() const override;
    void simulateData() override;

private:
    int randomObjectCount() const;
};

#endif
