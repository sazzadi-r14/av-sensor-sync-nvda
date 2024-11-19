#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Sensor.h"
#include <vector>
#include <memory>
#include <thread>
using namespace std;

class SensorManager {
public:
    void addSensor(unique_ptr<Sensor> sensor);
    void start();

private:
    vector<unique_ptr<Sensor>> sensors;
    vector<thread> sensorThreads;
};

#endif
