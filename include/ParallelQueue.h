#ifndef PARALLEL_QUEUE_H
#define PARALLEL_QUEUE_H

#include "SensorData.h"
#include <queue>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <vector>

class ParallelQueue {
    static const size_t MAX_SIZE = 1000; // Prevent unbounded growth

    std::queue<SensorData> queue;
    std::unordered_map<int, SensorData> latestReadings; // Latest reading per sensor
    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    void push(const SensorData& data);
    std::optional<SensorData> getLatest(int sensorId);
    std::unordered_map<int, SensorData> getAllLatest();
    std::vector<SensorData> getHistory();
    SensorData waitAndPop(); // Blocking call to retrieve data
};

#endif
