#ifndef LOGGINGSTATE_H
#define LOGGINGSTATE_H

#include "State.h"

class LoggingState : public State {
public:
    void enter(TPMS& tpms) override;
    void exit(TPMS& tpms) override;
    void handleEvent(TPMS& tpms, const std::string& event) override;
};

#endif // LOGGINGSTATE_H
