#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
public:
    virtual ~Sensor() {}
    virtual double simulateResponseTime() const = 0;
    virtual std::string generateData() const = 0;
};

#endif
