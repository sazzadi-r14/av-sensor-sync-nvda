#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>
#include <utility> // for pair
using namespace std;
class Sensor {
public:
    virtual ~Sensor() {}

    // Pure virtual functions to be implemented by child classes
    virtual string getType() const = 0;
    virtual string getModel() const = 0;
    virtual pair<int, int> getResponseRate() const = 0; // Best and worst response time
    virtual vector<int> getOutputShape() const = 0;
    virtual void simulateData() = 0;

protected:
    string type;
    string model;
    pair<int, int> responseRate; // {best, worst} response time in ms
    vector<int> outputShape;
};

#endif
