#include "SensorFactory.h"
using namespace std;

unique_ptr<Sensor> SensorFactory::createSensor(const string& type, const string& model, int fps) {
    if (type == "Camera") {
        return make_unique<CameraSensor>(model, fps);
    } else if (type == "Lidar") {
        return make_unique<LidarSensor>(model);
    } else if (type == "Radar") {
        return make_unique<RadarSensor>(model);
    } else if (type == "GNSS") {
        return make_unique<GNSSSensor>(model);
    } else {
        throw invalid_argument("Unknown sensor type");
    }
}
