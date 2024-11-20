#include "CameraSensor.h"
using namespace std;

CameraSensor::CameraSensor(const string& model, int fps) {
    this->type = "Camera";
    this->model = model;
    this->fps = fps;
    this->responseTime = 1000 / fps; // ms per frame
    this->responseRate = {responseTime, responseTime};
    this->outputShape = {2160, 3840, 3};
}

string CameraSensor::getType() const {
    return type;
}

string CameraSensor::getModel() const {
    return model;
}

pair<int, int> CameraSensor::getResponseRate() const {
    return responseRate;
}

vector<int> CameraSensor::getOutputShape() const {
    return outputShape;
}

// Return the variant representation of the output shape
SensorOutput CameraSensor::getOutputShapeVariant() const {
    return std::vector<std::vector<std::vector<int>>>(
        2160, std::vector<std::vector<int>>(3840, std::vector<int>(3)));
}


void CameraSensor::simulateData(ParallelQueue& queue, int sensorId) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(responseTime));

        // Simulate camera data
        SensorOutput data = std::vector<std::vector<std::vector<int>>>(
            2160, std::vector<std::vector<int>>(3840, std::vector<int>(3, 255)));

        SensorData sensorData{
            sensorId,
            "Camera",
            data,
            std::chrono::system_clock::now()
        };

        queue.push(sensorData);
    }
}
