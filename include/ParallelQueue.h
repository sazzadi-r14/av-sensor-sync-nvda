#ifndef PARALLEL_QUEUE_H
#define PARALLEL_QUEUE_H

#include "SensorData.h"
#include <queue>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <vector>

class ParallelQueue {
    static const size_t MAX_SIZE = 1000; // Prevent unbounded growth

    std::queue<SensorData> queue;
    std::unordered_map<int, SensorData> latestReadings; // Latest reading per sensor
    mutable std::mutex mtx;

public:
    void push(const SensorData& data);
    std::unordered_map<int, SensorData> retrieveLatest();
    std::vector<SensorData> retrieveAllAndClear();
};

#endif
