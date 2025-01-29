#include "../Headers/IdleState.h"
#include "../Headers/TPMS.h"
#include "../Headers/MonitoringState.h"

void IdleState::enter(TPMS& tpms) {
    std::cout << "Entering Idle State." << std::endl;
}

void IdleState::exit(TPMS& tpms) {
    std::cout << "Exiting Idle State." << std::endl;
}

void IdleState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "start") {
        tpms.setState(std::make_shared<MonitoringState>());
    } else {
        std::cout << "Invalid event in Idle State." << std::endl;
    }
}
