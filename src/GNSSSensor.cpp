#include "GNSSSensor.h"
using namespace std;

GNSSSensor::GNSSSensor(const string& model) {
    this->type = "GNSS";
    this->model = model;
    this->responseRate = {10, 50}; // GPS: 50ms-1000ms
    this->outputShape = {1, 11}; // Position: (latitude, longitude, altitude, speed, velocity, ax, ay, az, wx, wy, wz)
}

string GNSSSensor::getType() const {
    return type;
}

string GNSSSensor::getModel() const {
    return model;
}

pair<int, int> GNSSSensor::getResponseRate() const {
    return responseRate;
}

vector<int> GNSSSensor::getOutputShape() const {
    return outputShape;
}

void GNSSSensor::simulateData() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(responseRate.first));
        cout << "Lidar (" << model << ") generated point cloud data." << endl;
    }
}
