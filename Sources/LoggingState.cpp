#include "../Headers/LoggingState.h"
#include "../Headers/TPMS.h"
#include "../Headers/MonitoringState.h"
#include "../Headers/ErrorState.h"
#include <iostream>

void LoggingState::enter(TPMS& tpms) {
    std::cout << "Entering Logging State. Logging tyre data." << std::endl;
    try {
        tpms.startLogging();
    } catch (const std::exception& e) {
        std::cerr << "File logging failed: " << e.what() << std::endl;
        tpms.handleError(); // Transition to ErrorState
    }
}

void LoggingState::exit(TPMS& tpms) {
    std::cout << "Exiting Logging State." << std::endl;
}

void LoggingState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "monitor") {
        tpms.setState(std::make_unique<MonitoringState>());
    } else {
        std::cerr << "Invalid event in Logging State." << std::endl;
        tpms.handleError(); // Transition to ErrorState on unexpected event
    }
}
