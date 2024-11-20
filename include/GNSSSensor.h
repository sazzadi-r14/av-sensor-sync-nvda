#ifndef GNSS_SENSOR_H
#define GNSS_SENSOR_H

#include "Sensor.h"
#include "ParallelQueue.h"
#include <vector>
#include <string>

class GNSSSensor : public Sensor {
public:
    GNSSSensor(const std::string& model);

    std::string getType() const override;
    std::string getModel() const override;
    std::pair<int, int> getResponseRate() const override;
    std::vector<int> getOutputShape() const override;
     // Return the variant-based data representation
    SensorOutput getOutputShapeVariant() const override;
    void simulateData(ParallelQueue& queue, int sensorId) override;

private:
    std::vector<float> generateGNSSData() const; // Generates the 1x11 vector for GNSS
};

#endif
