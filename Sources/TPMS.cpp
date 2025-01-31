#include "../Headers/TPMS.h"
#include "../Headers/IdleState.h"
#include "../Headers/LoggingState.h"
#include "../Headers/MonitoringState.h"
#include "../Headers/ErrorState.h"
#include <thread>
#include <iostream>
#include <fstream> 

TPMS::TPMS() : log_thread_running(true), logThread([this]() { loggingTask(); }) {
    // currentState is a pointer of type Base class
    // At run time, it will point to appropriate state
    // This is Runtime polymorphism
    // At start, when TPMS system in instatiated, currentState points to Idle state.
    currentState = std::make_shared<IdleState>();
    currentState->enter(*this);

    std::cout << "TPMS object created. Logging thread started." << std::endl;
}

TPMS::~TPMS() {
    {
        std::lock_guard<std::mutex> lock(logMutex);
        log_thread_running = false;  // Signal thread to stop
    }
    
    if (logThread.joinable()) {
        logThread.join();  // Wait for the thread to finish execution
    }
    std::cout << "TPMS object destroyed. Logging thread safely joined." << std::endl;

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

    // Create a new thread to handle continuous tyre pressure monitoring
    dataThread = std::thread([this]() {
        while (running) {
            try {
                acquireSensorData();
                // delay to simulate sensor read interval
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulated delay
            } catch (const std::exception& e) {
                std::cerr << "Data acquisition thread failed: " << e.what() << std::endl;
            
                // Handle the error by transitioning to an error state
                handleError();
            
                // Stop the monitoring process to prevent further faulty readings
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
    //     setState(std::make_shared<ErrorState>());
    // }
}

// This function is responsible for simulating the retrieval of tyre pressure data from sensors.
void TPMS::acquireSensorData() {
    // Simulated sensor failure
    // generates numbers 0, 1, 2, etc upto n-1. If the result is 0, it simulates a failure.
    int random = rand() % 1000;
    if (random == 0) {
        // This exception is caught in the lambda function inside startMonitoring(), 
        // ensuring proper error handling.
        throw std::runtime_error("Sensor failure detected!");
    }
        
    // Ensure thread safety when accessing shared resources (tyreData vector and log file)
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety
    static int pressure = 0;
    tyreData.push_back(std::string("Tyre1: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre2: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre3: " + std::to_string((pressure++)%50) + " PSI"));
    tyreData.push_back(std::string("Tyre4: " + std::to_string((pressure++)%50) + " PSI"));

    // Log a message indicating that tyre data collection was completed
    // We collect the data in local buffer.
    // We will actually write buffer data into logfile after fixed interval (in a thread)
    std::ofstream logFile("TyreData.log", std::ios::app);  // Open file in append mode
    std::cout << "***** Tyre pressure for all 4 tyres collected *****\n";
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
    // std::lock_guard<std::mutex> lock(logMutex);  // Ensure thread safety

    try {
        // If logFile is a local variable. 
        // It will be closed automatically when the function ends.
        std::ofstream logFile("TyreData.log", std::ios::app);  // Open file in append mode
        if (!logFile) {
            throw std::ios_base::failure("Failed to open log file!");
        }

        for (const auto& data : tyreData) {
            std::cout << "data: " << data << std::endl;
            logFile << data << std::endl;  // Write sensor data to log file
        }
        logFile.close();  // Close the file explicitly (optional)
        tyreData.clear(); // ✅ Clear the vector after writing to avoid duplicate entries
        std::cout << "Logging complete. Data written to TyreData.log" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error during logging: " << e.what() << std::endl;
    }
    // Enter into "monitoring" state again
    setState(std::make_shared<MonitoringState>());
}

void TPMS::handleError() {
    std::cout << "Error encountered! Switching to Error State." << std::endl;
    setState(std::make_shared<ErrorState>());
}


