#include "GNSSSensor.h"
using namespace std;

GNSSSensor::GNSSSensor(const string& model) {
    this->type = "GNSS";
    this->model = model;
    this->responseRate = {50, 1000}; // GPS: 50ms-1000ms
    this->outputShape = {1, 3}; // Position: (latitude, longitude, altitude)
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
    thread imuThread(&GNSSSensor::simulateIMU, this);
    thread positionThread(&GNSSSensor::simulatePosition, this);

    imuThread.join();
    positionThread.join();
}

void GNSSSensor::simulateIMU() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(5));
        cout << "GNSS IMU generated accelerometer and gyroscope data." << endl;
    }
}

void GNSSSensor::simulatePosition() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "GNSS generated position data (latitude, longitude, altitude)." << endl;
    }
}
