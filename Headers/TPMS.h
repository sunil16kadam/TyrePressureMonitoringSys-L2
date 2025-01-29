#ifndef TPMS_H
#define TPMS_H

#include "State.h"
#include <memory>

class TPMS {
public:
    TPMS();
    void setState(std::shared_ptr<State> newState);
    void handleEvent(const std::string& event);
    void startMonitoring();
    void stopMonitoring();
    void startLogging();
    bool connectToDashboard();
    void handleError();
    void acquireSensorData();

private:
    std::shared_ptr<State> currentState;
};

#endif // TPMS_H
