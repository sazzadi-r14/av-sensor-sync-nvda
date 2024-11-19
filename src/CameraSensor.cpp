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

void CameraSensor::simulateData() {
    
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(responseTime));
        cout << "Camera (" << model << ") generated a frame." << endl;
    }
}
