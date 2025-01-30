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
    std::mutex logMutex;                    // Ensure thread-safe logging
    std::vector<std::string> tyreData;      // Stores sensor data
    std::atomic<bool> running{false};       // Flag to control thread execution

};

#endif // TPMS_H
