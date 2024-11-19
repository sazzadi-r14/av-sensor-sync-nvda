#include "LidarSensor.h"
using namespace std;

LidarSensor::LidarSensor(const string& model) {
    this->type = "Lidar";
    this->model = model;
    this->responseRate = {50, 50}; // Fixed at 20 Hz (50ms)
    this->outputShape = {88462, 4};
}

string LidarSensor::getType() const {
    return type;
}

string LidarSensor::getModel() const {
    return model;
}

pair<int, int> LidarSensor::getResponseRate() const {
    return responseRate;
}

vector<int> LidarSensor::getOutputShape() const {
    return outputShape;
}

void LidarSensor::simulateData() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(responseRate.first));
        cout << "Lidar (" << model << ") generated point cloud data." << endl;
    }
}
