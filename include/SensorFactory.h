#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include "Sensor.h"
#include "CameraSensor.h"
#include "LidarSensor.h"
#include "RadarSensor.h"
#include "GNSSSensor.h"
#include <memory>
using namespace std;

class SensorFactory {
public:
    static unique_ptr<Sensor> createSensor(const string& type, const string& model, int fps = 30);
};

#endif
