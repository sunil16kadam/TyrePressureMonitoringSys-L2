#include "../Headers/MonitoringState.h"
#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/ErrorState.h"
#include "../Headers/LoggingState.h"
#include <thread>
#include <chrono>
#include <iostream>

void MonitoringState::enter(TPMS& tpms) {
    std::cout << "Entering Monitoring State." << std::endl;
    try {
        tpms.startMonitoring();
    } catch (const std::exception& e) {
        std::cerr << "Error in Monitoring State: " << e.what() << std::endl;
        tpms.handleError(); // Transition to ErrorState
    }
    // Automatically transition to Logging State after 1 minutes
    std::thread([&tpms]() {
        //std::this_thread::sleep_for(std::chrono::minutes(1));
        std::this_thread::sleep_for(std::chrono::seconds(10));
        tpms.handleEvent("log");  // Triggers Logging State
    }).detach();
}

void MonitoringState::exit(TPMS& tpms) {
    std::cout << "Exiting Monitoring State." << std::endl;
    tpms.stopMonitoring();
}

void MonitoringState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "stop") {
        tpms.setState(std::make_unique<IdleState>());
    } else if (event == "log") {
        tpms.setState(std::make_unique<LoggingState>()); // Transition to Logging State
    } else {
        std::cerr << "Invalid event in Monitoring State." << std::endl;
        tpms.handleError(); // Transition to Error State on unexpected event
    }
}
