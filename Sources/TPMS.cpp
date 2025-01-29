#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/LoggingState.h"
#include "../Headers/ErrorState.h"
#include <thread>
#include <iostream>
#include <fstream> 

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

// This function starts monitoring tyre pressure by launching a separate thread.
void TPMS::startMonitoring() {
    std::cout << "TPMS started monitoring tyres." << std::endl;
    // try-catch block to handle any exceptions that might occur during thread creation.
    try {
           // Creates a new thread (dataThread) that will execute the lambda function.
           // The [this] captures the current instance of TPMS so that 
           // the lambda function can call acquireSensorData(), which is a member function.
         std::thread dataThread([this]() {
            try {
                acquireSensorData();     // read tyre pressure data.
            } catch (const std::exception& e) {
                std::cerr << "Data acquisition thread failed: " << e.what() << std::endl;
                handleError();           // Transition to ErrorState
            }
         });
         dataThread.detach();          // Let the thread run independently in the background 
                                       // without blocking the main program.
                                       // This means:
                                       // - The thread cannot be joined later.
                                       // - The program must ensure that TPMS remains valid while the thread runs.
    } catch (...) {
        std::cerr << "Failed to start monitoring thread." << std::endl;
        handleError();
    }

    // try {
    //     // Simulating a potential communication failure
    //     if (!connectToDashboard()) {
    //         throw std::runtime_error("Failed to connect to vehicle dashboard.");
    //     }
    // } catch (const std::exception& e) {
    //     std::cerr << "Monitoring Error: " << e.what() << std::endl;
    //     handleError(); // Transition to ErrorState
    // }
}

// This function is responsible for simulating the retrieval of tyre pressure data from sensors.
void TPMS::acquireSensorData() {
       // Simulated sensor failure
       // generates numbers 0, 1, or 2. If the result is 0, it simulates a failure.
     if (rand() % 3 == 0) {
       // This exception is caught in the lambda function inside startMonitoring(), 
       // ensuring proper error handling.
        throw std::runtime_error("Sensor failure detected!");
     }
     tyreData.push_back(std::string("Tyre1: 32 PSI"));
     tyreData.push_back(std::string("Tyre2: 30 PSI"));
     tyreData.push_back(std::string("Tyre3: 31 PSI"));
     tyreData.push_back(std::string("Tyre4: 29 PSI"));
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
    std::lock_guard<std::mutex> lock(logMutex);  // Ensure thread safety

    try {
        std::ofstream logFile("TyreData.log", std::ios::app);  // Open file in append mode
        if (!logFile) {
            throw std::ios_base::failure("Failed to open log file!");
        }

        for (const auto& data : tyreData) {
            logFile << data << std::endl;  // Write sensor data to log file
        }

        std::cout << "Logging complete. Data written to TyreData.log" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error during logging: " << e.what() << std::endl;
    }
}

void TPMS::handleError() {
    std::cout << "Error encountered! Switching to Error State." << std::endl;
    setState(std::make_shared<ErrorState>());
}


