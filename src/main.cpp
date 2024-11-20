#include "SensorFactory.h"
#include "SensorManager.h"

int main() {
    SensorManager manager;

    // Add multiple instances of sensors
    // manager.addSensor(SensorFactory::createSensor("Camera", "Sony IMX728", 30), 1);
    // manager.addSensor(SensorFactory::createSensor("Camera", "Sony IMX728", 30), 2);
    manager.addSensor(SensorFactory::createSensor("Lidar", "Luminar Iris"), 3);
    manager.addSensor(SensorFactory::createSensor("Radar", "Arbe A4"), 4);
    manager.addSensor(SensorFactory::createSensor("GNSS", "NovAtel PwrPak7D-E1"), 5);

    
    cout << "Waiting 2s Before Starting The Sensors" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Start the manager
    manager.start();

    // // Allow simulation to run for some time
    // std::this_thread::sleep_for(std::chrono::seconds(10));

    // // Stop the manager and threads
    // manager.stop();
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    

    return 0;
}
