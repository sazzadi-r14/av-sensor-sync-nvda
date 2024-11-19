#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H

#include "Sensor.h"
#include <iostream>
#include <thread>
#include <chrono> // For timing
using namespace std;

class CameraSensor : public Sensor {
public:
    CameraSensor(const string& model, int fps);
    string getType() const override;
    string getModel() const override;
    pair<int, int> getResponseRate() const override;
    vector<int> getOutputShape() const override;
    void simulateData(ParallelQueue& queue, int sensorId) override;

private:
    int fps; // Frames per second
    int responseTime; // Calculated from fps
};

#endif
