#include "RadarSensor.h"
using namespace std;

RadarSensor::RadarSensor(const string& model) {
    this->type = "Radar";
    this->model = model;
    this->responseRate = {20, 50}; // 20ms to 50ms
    this->outputShape = {0, 4}; // Dynamic number of objects
}

string RadarSensor::getType() const {
    return type;
}

string RadarSensor::getModel() const {
    return model;
}

pair<int, int> RadarSensor::getResponseRate() const {
    return responseRate;
}

vector<int> RadarSensor::getOutputShape() const {
    return {randomObjectCount(), 4};
}

void RadarSensor::simulateData() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(responseRate.first));
        int objects = randomObjectCount();
        cout << "Radar (" << model << ") detected " << objects << " objects." << endl;
    }
}

int RadarSensor::randomObjectCount() const {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 50); // Randomly choose 10 to 50 objects
    return dis(gen);
}
