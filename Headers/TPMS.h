#ifndef TPMS_H
#define TPMS_H

#include "State.h"
#include <memory>
#include <thread>

class TPMS {
public:
    TPMS();
    ~TPMS();
    void setState(std::shared_ptr<State> newState);
    void handleEvent(const std::string& event);
    void startMonitoring();
    void stopMonitoring();
    void startLogging();
    bool connectToDashboard();
    void handleError();
    void acquireSensorData();

private:
    // currentState is a pointer of type Base class
    // At run time, it will point to appropriate state
    // This is Runtime polymorphism
    // At start, when TPMS system in instatiated, currentState points to Idle
    std::shared_ptr<State> currentState;

    std::thread dataThread;
    std::mutex mutex_tyre_data;                    // Ensure thread-safe logging
    std::vector<std::string> tyreData;      // Stores sensor data
    std::atomic<bool> flag_data_sensing_thread_running{false};       // Flag to control thread execution
    std::atomic<bool> flag_data_logger_thread_running;       // Flag to control thread execution

public:
    std::thread logThread;
    void loggingTask();

    void set_data_sensing_thread_running() {
        flag_data_sensing_thread_running = true;
    }
    void reset_data_sensing_thread_running() {
        flag_data_sensing_thread_running = false;
    }

};

#endif // TPMS_H
