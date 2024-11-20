#include "ParallelQueue.h"
#include <iostream>

void ParallelQueue::push(const SensorData& data) {
    std::lock_guard<std::mutex> lock(mtx);

    // Update the latest reading for the given sensor
    latestReadings[data.sensorId] = data;

    // Add data to the queue, but prevent overflow
    queue.push(data);
    if (queue.size() > MAX_SIZE) {
        // std::cout << "Warning: Queue size exceeded maximum size of " << MAX_SIZE << ". Clearing queue.\n";
        queue.pop();
    }
}

std::unordered_map<int, SensorData> ParallelQueue::retrieveLatest() {
    std::lock_guard<std::mutex> lock(mtx);
    return latestReadings; // Return the latest readings for all sensors
}

std::vector<SensorData> ParallelQueue::retrieveAllAndClear() {
    std::lock_guard<std::mutex> lock(mtx);

    // Retrieve all data from the queue
    std::vector<SensorData> allData;
    while (!queue.empty()) {
        allData.push_back(queue.front());
        queue.pop();
    }

    // Clear the latest readings as well
    latestReadings.clear();

    return allData;
}
