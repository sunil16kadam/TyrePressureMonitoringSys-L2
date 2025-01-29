#include "../Headers/ErrorState.h"
#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"

void ErrorState::enter(TPMS& tpms) {
    std::cout << "Entering Error State. System encountered an issue." << std::endl;
}

void ErrorState::exit(TPMS& tpms) {
    std::cout << "Exiting Error State. System recovered." << std::endl;
}

void ErrorState::handleEvent(TPMS& tpms, const std::string& event) {
    if (event == "recover") {
        tpms.setState(std::make_shared<IdleState>());
    } else {
        std::cout << "Invalid event in Error State. Awaiting recovery action." << std::endl;
    }
}
