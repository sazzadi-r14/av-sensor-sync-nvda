#include "SensorManager.h"
#include <vector>
#include <string>
#include <chrono>
#include <variant>
#include <queue>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <optional>

using namespace std;

struct SensorData {
    int sensorId;  // Unique ID for the sensor
    std::string sensorType;  // Type of sensor (e.g., "Camera", "Radar")
    std::variant<std::vector<double>, std::vector<std::vector<double>>, std::vector<std::vector<std::vector<double>>>> data;  // Dynamic shape
    std::chrono::system_clock::time_point timestamp;  // Time of data generation
};



class ParallelQueue {
    static const size_t MAX_SIZE = 1000;  // Prevent unbounded growth

    std::queue<SensorData> queue;
    std::unordered_map<int, SensorData> latestReadings;  // Latest data per sensor ID
    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    void push(SensorData data) {
        std::lock_guard<std::mutex> lock(mtx);

        // Update latest reading for this sensor
        latestReadings[data.sensorId] = data;

        // Add to queue, prevent overflow
        queue.push(std::move(data));
        if (queue.size() > MAX_SIZE) {
            queue.pop();  // Remove oldest if too many
        }

        cv.notify_one();
    }

    std::optional<SensorData> getLatest(int sensorId) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = latestReadings.find(sensorId);
        if (it != latestReadings.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    std::unordered_map<int, SensorData> getAllLatest() {
        std::lock_guard<std::mutex> lock(mtx);
        return latestReadings;
    }

    std::vector<SensorData> getHistory() {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<SensorData> data;
        auto tempQueue = queue;  // Make a copy
        while (!tempQueue.empty()) {
            data.push_back(std::move(tempQueue.front()));
            tempQueue.pop();
        }
        return data;
    }
};




void SensorManager::addSensor(unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void SensorManager::start() {
    for (auto& sensor : sensors) {
        sensorThreads.emplace_back(&Sensor::simulateData, sensor.get());
    }

    for (auto& thread : sensorThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
