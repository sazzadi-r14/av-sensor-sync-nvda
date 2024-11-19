#ifndef SENSOR_H
#define SENSOR_H

#include "SensorData.h"
#include "ParallelQueue.h"
#include <string>
#include <vector>
#include <utility> // for pair
using namespace std;
class Sensor {
public:
    virtual ~Sensor() {}

    virtual std::string getType() const = 0;
    virtual std::string getModel() const = 0;
    virtual std::pair<int, int> getResponseRate() const = 0;
    virtual std::vector<int> getOutputShape() const = 0;

    virtual void simulateData(ParallelQueue& queue, int sensorId) = 0; // Pass queue to push data

protected:
    string type;
    string model;
    pair<int, int> responseRate; // {best, worst} response time in ms
    vector<int> outputShape;
};

#endif