#include "ParallelQueue.h"

void ParallelQueue::push(const SensorData& data) {
    std::lock_guard<std::mutex> lock(mtx);

    // Update the latest reading for the given sensor
    latestReadings[data.sensorId] = data;

    // Add data to the queue, but prevent overflow
    queue.push(data);
    if (queue.size() > MAX_SIZE) {
        queue.pop();
    }

    // Notify any waiting threads
    cv.notify_one();
}

std::optional<SensorData> ParallelQueue::getLatest(int sensorId) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = latestReadings.find(sensorId);
    if (it != latestReadings.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::unordered_map<int, SensorData> ParallelQueue::getAllLatest() {
    std::lock_guard<std::mutex> lock(mtx);
    return latestReadings;
}

std::vector<SensorData> ParallelQueue::getHistory() {
    std::lock_guard<std::mutex> lock(mtx);

    std::vector<SensorData> data;
    auto tempQueue = queue; // Copy the queue
    while (!tempQueue.empty()) {
        data.push_back(tempQueue.front());
        tempQueue.pop();
    }
    return data;
}

SensorData ParallelQueue::waitAndPop() {
    std::unique_lock<std::mutex> lock(mtx);

    // Wait until there's data in the queue
    cv.wait(lock, [this] { return !queue.empty(); });

    SensorData data = queue.front();
    queue.pop();
    return data;
}
