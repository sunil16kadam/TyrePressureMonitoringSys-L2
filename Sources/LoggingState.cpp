#include "../Headers/LoggingState.h"
#include "../Headers/TPMS.h"
#include "../Headers/MonitoringState.h"

void LoggingState::enter(TPMS& tpms) {
    std::cout << "Entering Logging State. Logging tyre data." << std::endl;
    tpms.startLogging(); // Assumes a method to log data
}

void LoggingState::exit(TPMS& tpms) {
    std::cout << "Exiting Logging State." << std::endl;
}

void LoggingState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "monitor") {
        tpms.setState(std::make_shared<MonitoringState>());
    } else {
        std::cout << "Invalid event in Logging State." << std::endl;
    }
}
