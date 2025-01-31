#include "../Headers/MonitoringState.h"
#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/ErrorState.h"
#include "../Headers/LoggingState.h"
//#include <jthread>
#include <future>
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
        tpms.setState(std::make_shared<ErrorState>());
    }
}
