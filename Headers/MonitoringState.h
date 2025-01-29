#ifndef MONITORINGSTATE_H
#define MONITORINGSTATE_H

#include "State.h"

class MonitoringState : public State {
public:
    void enter(TPMS& tpms) override;
    void exit(TPMS& tpms) override;
    void handleEvent(TPMS& tpms, const std::string& event) override;
};

#endif // MONITORINGSTATE_H
