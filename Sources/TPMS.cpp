#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/LoggingState.h"
#include "../Headers/ErrorState.h"
#include <iostream>

TPMS::TPMS() {
    currentState = std::make_shared<IdleState>();
    currentState->enter(*this);
}

void TPMS::setState(std::shared_ptr<State> newState) {
    currentState->exit(*this);
    currentState = newState;
    currentState->enter(*this);
}

void TPMS::handleEvent(const std::string& event) {
    currentState->handleEvent(*this, event);
}

void TPMS::startMonitoring() {
    std::cout << "TPMS started monitoring tyres." << std::endl;
    // Add monitoring logic (e.g., spawn threads to collect data)
}

void TPMS::stopMonitoring() {
    std::cout << "TPMS stopped monitoring tyres." << std::endl;
    // Add logic to stop monitoring
}

void TPMS::startLogging() {
    std::cout << "Logging tyre data..." << std::endl;
    // Implement logging functionality
}

void TPMS::handleError() {
    std::cout << "Error encountered! Switching to Error State." << std::endl;
    setState(std::make_shared<ErrorState>());
}
