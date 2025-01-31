#include "../Headers/IdleState.h"
#include "../Headers/ErrorState.h"
#include "../Headers/TPMS.h"
#include "../Headers/MonitoringState.h"

void IdleState::enter(TPMS& tpms) {
    std::cout << "Entered Idle State." << std::endl;
    std::cout << "Awaiting start command..." << std::endl;
}

void IdleState::exit(TPMS& tpms) {
    std::cout << "Exiting Idle State." << std::endl;
}

void IdleState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "start") {
        tpms.setState(std::make_shared<MonitoringState>());
    } else {
        // In this case, I have chosen to wait for "start" event, instaed of switching to ErrorState
        //tpms.setState(std::make_shared<ErrorState>());
        std::cout << "Invalid event in Error State. Awaiting recovery action." << std::endl;
    }
}
