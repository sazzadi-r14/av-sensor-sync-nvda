#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include "Sensor.h"

class SensorManager {
public:
    void addSensor(Sensor* sensor);
    void collectData();

private:
    std::vector<Sensor*> sensors;
};

#endif
