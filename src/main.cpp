#include "SensorFactory.h"
#include "SensorManager.h"
using namespace std;

int main() {
    SensorManager manager;

    // Add sensors
    manager.addSensor(SensorFactory::createSensor("Camera", "Sony IMX728", 30));
    manager.addSensor(SensorFactory::createSensor("Lidar", "Luminar Iris"));
    manager.addSensor(SensorFactory::createSensor("Radar", "Arbe A4"));
    manager.addSensor(SensorFactory::createSensor("GNSS", "NovAtel PwrPak7D-E1"));

    // Start the simulation
    manager.start();

    return 0;
}
