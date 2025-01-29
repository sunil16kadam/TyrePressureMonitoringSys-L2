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
    try {
        // Simulating a potential communication failure
        if (!connectToDashboard()) {
            throw std::runtime_error("Failed to connect to vehicle dashboard.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Monitoring Error: " << e.what() << std::endl;
        handleError(); // Transition to ErrorState
    }
}

bool TPMS::connectToDashboard() {
    // Simulating a 50% chance of failure
    return rand() % 2;
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
///
// #include <thread>

// void TPMS::startMonitoring() {
//     std::cout << "TPMS started monitoring tyres." << std::endl;
//     try {
//         std::thread dataThread([this]() {
//             try {
//                 acquireSensorData();
//             } catch (const std::exception& e) {
//                 std::cerr << "Data acquisition thread failed: " << e.what() << std::endl;
//                 handleError(); // Transition to ErrorState
//             }
//         });

//         dataThread.detach(); // Let the thread run independently
//     } catch (...) {
//         std::cerr << "Failed to start monitoring thread." << std::endl;
//         handleError();
//     }
// }

// void TPMS::acquireSensorData() {
//     // Simulated sensor failure
//     if (rand() % 3 == 0) {
//         throw std::runtime_error("Sensor failure detected!");
//     }
// }
