#include "Sensor.h"
#include <random>
#include <sstream>

class LidarSensor : public Sensor {
public:
    double simulateResponseTime() const override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(10.0, 2.0); // Mean=10ms, SD=2ms
        return d(gen);
    }

    std::string generateData() const override {
        std::ostringstream ss;
        ss << "Lidar data at timestamp " << simulateResponseTime();
        return ss.str();
    }
};
