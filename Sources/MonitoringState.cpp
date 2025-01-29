#include "../Headers/MonitoringState.h"
#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"

void MonitoringState::enter(TPMS& tpms) {
    std::cout << "Entering Monitoring State." << std::endl;
    tpms.startMonitoring();
}

void MonitoringState::exit(TPMS& tpms) {
    std::cout << "Exiting Monitoring State." << std::endl;
    tpms.stopMonitoring();
}

void MonitoringState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "stop") {
        tpms.setState(std::make_shared<IdleState>());
    } else {
        std::cout << "Invalid event in Monitoring State." << std::endl;
    }
}
