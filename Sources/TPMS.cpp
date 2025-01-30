#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/LoggingState.h"
#include "../Headers/ErrorState.h"
#include <thread>
#include <iostream>
#include <fstream> 

TPMS::TPMS() {
    // currentState is a pointer of type Base class
    // At run time, it will point to appropriate state
    // This is Runtime polymorphism
    // At start, when TPMS system in instatiated, currentState points to Idle state.
    currentState = std::make_shared<IdleState>();
    currentState->enter(*this);
}

TPMS::~TPMS() {
    stopMonitoring(); // Properly stop the thread before exiting
}

// Transition to new state
void TPMS::setState(std::shared_ptr<State> newState) {
    currentState->exit(*this);
    currentState = newState;
    currentState->enter(*this);
}

void TPMS::handleEvent(const std::string& event) {
    currentState->handleEvent(*this, event);
    // spk: Should we check the current state and acceptable event in this current state here.
    // and exit or error or ignore on invalid event.
}

// This function starts monitoring tyre pressure by launching a separate thread.
void TPMS::startMonitoring() {
    if (running) {
        std::cout << "Monitoring is already running. Ignoring duplicate call.\n";
        return;  // Prevents starting a new thread if one is already running
    }

    std::cout << "TPMS started monitoring tyres." << std::endl;
    running = true;  // Set flag to indicate monitoring is active

    dataThread = std::thread([this]() {
        while (running) {
            try {
                acquireSensorData();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulated delay
            } catch (const std::exception& e) {
                std::cerr << "Data acquisition thread failed: " << e.what() << std::endl;
                handleError();
                running = false;  // Stop monitoring on error
            }
        }
    });

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
    int random = rand() % 1000;
    std::cout << "random: " << random << std::endl;

    if (random == 0) {
        // This exception is caught in the lambda function inside startMonitoring(), 
        // ensuring proper error handling.
        throw std::runtime_error("Sensor failure detected!");
    }
        
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety
    static int pressure = 0;
    tyreData.push_back(std::string("Tyre1: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre2: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre3: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre4: " + std::to_string((pressure++)%50) + " PSI"));
    //  tyreData.push_back(std::string("Tyre2: 30 PSI"));
    //  tyreData.push_back(std::string("Tyre3: 31 PSI"));
    //  tyreData.push_back(std::string("Tyre4: 29 PSI"));
    std::ofstream logFile("TyreData.log", std::ios::app);  // Open file in append mode
    logFile << "***** Tyre pressure for all 4 tyres collected *****\n";
    logFile.close();  // Close the file explicitly (optional)
}

bool TPMS::connectToDashboard() {
    // Simulating a 50% chance of failure
    return rand() % 2;
}

void TPMS::stopMonitoring() {
    if (!running) return;  // If monitoring is already stopped, do nothing

    running = false;  // Set flag to stop the loop
    if (dataThread.joinable()) {
        dataThread.join();  // Wait for the thread to exit
    }
    std::cout << "Monitoring stopped.\n";
}

void TPMS::startLogging() {
    
    std::cout << "Logging tyre data..." << std::endl;
    
    // Implement logging functionality
    std::lock_guard<std::mutex> lock(logMutex);  // Ensure thread safety

    try {
        // If logFile is a local variable. 
        // It will be closed automatically when the function ends.
        std::ofstream logFile("TyreData.log", std::ios::app);  // Open file in append mode
        if (!logFile) {
            throw std::ios_base::failure("Failed to open log file!");
        }

        for (const auto& data : tyreData) {
            logFile << data << std::endl;  // Write sensor data to log file
        }
        logFile.close();  // Close the file explicitly (optional)
        tyreData.clear(); // ✅ Clear the vector after writing to avoid duplicate entries
        std::cout << "Logging complete. Data written to TyreData.log" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error during logging: " << e.what() << std::endl;
    }
    // spk: Enter into "monitoring" state again
    handleEvent("monitor");  // Enter into "monitoring" state again
}

void TPMS::handleError() {
    std::cout << "Error encountered! Switching to Error State." << std::endl;
    setState(std::make_shared<ErrorState>());
}


