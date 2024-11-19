#ifndef GNSS_SENSOR_H
#define GNSS_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
using namespace std;

class GNSSSensor : public Sensor {
public:
    GNSSSensor(const string& model);
    string getType() const override;
    string getModel() const override;
    pair<int, int> getResponseRate() const override;
    vector<int> getOutputShape() const override;
    void simulateData() override;

private:
    void simulateIMU();
    void simulatePosition();
};

#endif
